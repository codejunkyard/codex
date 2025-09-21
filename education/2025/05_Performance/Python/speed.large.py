import time
from Bio import SeqIO

PATTERN = "TTGACA"
FILENAME = "../GCF_000001405.26_GRCh38_genomic.fna"

def read_fna(filename):
    sequence_chunks = []

    with open(filename, "r") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith(">"):
                continue  # skip headers and empty lines
            sequence_chunks.append(line)

    sequence = "".join(sequence_chunks)
    return sequence

def search_pattern(genome, pattern):
    """Count occurrences of pattern in genome."""
    count = 0
    pat_len = len(pattern)
    genome_len = len(genome)

    for i in range(genome_len - pat_len + 1):
        if genome[i:i+pat_len] == pattern:
            count += 1
    return count

def main():
    genome = read_fna(FILENAME)
    pattern = "ATGCGT"

    start = time.time()
    count = search_pattern(genome, pattern)
    end = time.time()

    print(f"Pattern '{pattern}' found {count} times")
    print(f"Search took {end - start:.3f} seconds")

if __name__ == "__main__":
    main()
