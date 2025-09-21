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

// Naive pattern search
int searchPattern(const char *sequence, size_t seqLen, const char *pattern) {
    size_t patLen = strlen(pattern);
    int count = 0;

    for (size_t i = 0; i <= seqLen - patLen; i++) {
        size_t j = 0;
        while (j < patLen && sequence[i + j] == pattern[j]) j++;
        if (j == patLen) count++;
    }
    return count;
}

int main() {
    const char *filename = "../ecoli_genome.fasta"; // replace with your FASTA file
    size_t seqLen = 0;
    char *genome = readFasta(filename, &seqLen);
    if (!genome) return 1;

    printf("Genome loaded: %zu bases\n", seqLen);

    clock_t start = clock();
    int count = searchPattern(genome, seqLen, PATTERN);
    clock_t end = clock();

    printf("Pattern '%s' found %d times\n", PATTERN, count);
    printf("Search took %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(genome);
    return 0;
}
