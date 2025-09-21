#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PATTERN "TTGACA"

// Function to read a FASTA file into a single sequence string
char* readFasta(const char *filename, size_t *seqLen) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = malloc(fileSize + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    size_t index = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '>') continue; // skip header lines
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] != '\n') buffer[index++] = line[i];
        }
    }
    buffer[index] = '\0';
    *seqLen = index;
    fclose(file);
    return buffer;
}

char* readFna(const char *filename, size_t *seqLen) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen");
        return NULL;
    }

    size_t capacity = 1024 * 1024;   // start with 1 MB buffer
    char *sequence = malloc(capacity);
    if (!sequence) {
        perror("malloc");
        fclose(file);
        return NULL;
    }

    *seqLen = 0;
    char buffer[8192];

    while (fgets(buffer, sizeof(buffer), file)) {
        if (buffer[0] == '>') continue; // skip headers

        // strip newline
        buffer[strcspn(buffer, "\r\n")] = '\0';
        size_t lineLen = strlen(buffer);

        // grow buffer if needed
        if (*seqLen + lineLen >= capacity) {
            capacity *= 2;
            char *tmp = realloc(sequence, capacity);
            if (!tmp) {
                perror("realloc");
                free(sequence);
                fclose(file);
                return NULL;
            }
            sequence = tmp;
        }

        memcpy(sequence + *seqLen, buffer, lineLen);
        *seqLen += lineLen;
    }

    fclose(file);

    // null terminate
    sequence[*seqLen] = '\0';

    return sequence;
}

// Naive pattern search
int searchPattern(const char *genome, size_t genomeLength, const char *pattern) {
    size_t patternLength = strlen(pattern);
    int count = 0;

    if (patternLength == 0 || genomeLength < patternLength) return 0;

    for (size_t i = 0; i <= genomeLength - patternLength; i++) {
        size_t j = 0;
        //while (j < patternLength && genome[i + j] == pattern[j]) j++;
        //if (j == patternLength) count++;
        if (memcmp(genome + i, pattern, patternLength) == 0) {
            count++;
        }
    }

    return count;
}

int main() {
    const char *filename = "../GCF_000001405.26_GRCh38_genomic.fna";
    size_t seqLen = 0;
    char *genome = readFna(filename, &seqLen);
    if (!genome) return 1;

    printf("Genome loaded: %zu bases\n", seqLen);

    const char *pattern = "ATGCGT";

    clock_t start = clock();
    size_t count = searchPattern(genome, seqLen, pattern);
    clock_t end = clock();

    printf("Pattern '%s' occurs %zu times\n", pattern, count);
    printf("Search took %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(genome);
    return 0;
}
