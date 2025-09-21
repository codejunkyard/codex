import time

PATTERN = "TTGACA"
FILENAME = "../ecoli_genome.fasta"  # adjust path as needed

# Read FASTA file into a single sequence string
def read_fasta(filename):
    sequence = []
    with open(filename, "r") as f:
        for line in f:
            if line.startswith(">"):
                continue  # skip headers
            sequence.append(line.strip())  # remove newline
    return "".join(sequence)

# Naive pattern search
def search_pattern(sequence, pattern):
    count = 0
    pat_len = len(pattern)
    for i in range(len(sequence) - pat_len + 1):
        if sequence[i:i+pat_len] == pattern:
            count += 1
    return count

def main():
    genome = read_fasta(FILENAME)
    print(f"Genome loaded: {len(genome)} bases")

    start = time.time()
    count = search_pattern(genome, PATTERN)
    end = time.time()

    print(f"Pattern '{PATTERN}' found {count} times")
    print(f"Search took {end - start:.3f} seconds")

if __name__ == "__main__":
    main()
