# We'll run a small, real-crypto demonstration using Bitcoin-style algorithms:
# - double SHA-256 of a simplified header
# - check validity by comparing the hash interpreted as a big integer to a target
# - target corresponds to "difficulty" measured in leading hex zeros
#
# This is educational only and mines on a tiny difficulty so it finishes quickly.

import hashlib, time
from dataclasses import dataclass

def double_sha256_bytes(b: bytes) -> bytes:
    return hashlib.sha256(hashlib.sha256(b).digest()).digest()

@dataclass
class SimpleBitcoinHeader:
    version: int
    prev_hash: str   # hex string
    merkle_root: str # hex string
    timestamp: int
    bits_difficulty_hex_zeros: int  # we'll model difficulty as number of leading hex zeros

    def serialize(self, nonce: int) -> bytes:
        # Simplified serialization (not Bitcoin's real binary format), but includes all fields:
        s = (
            f"{self.version:08x}"
            f"{self.prev_hash}"
            f"{self.merkle_root}"
            f"{self.timestamp:08x}"
            f"{nonce:08x}"
        )
        return bytes.fromhex(s)

def mine(header: SimpleBitcoinHeader, max_nonce=5_000_000, show_progress=True):
    difficulty = header.bits_difficulty_hex_zeros
    # Compute numeric target: valid if hash_int <= 2**(256 - difficulty*4) - 1
    if difficulty < 0 or difficulty > 64:
        raise ValueError("difficulty (hex zeros) must be 0..64")
    target = (1 << (256 - difficulty*4)) - 1
    if show_progress:
        print(f"Difficulty: {difficulty} hex zeros -> target = 2**(256 - {difficulty*4}) - 1")
        print(f"Target (hex, truncated): {target.to_bytes(32,'big').hex()[:difficulty]}...")

    start = time.time()
    tries = 0
    for nonce in range(max_nonce):
        hdr = header.serialize(nonce)
        h = double_sha256_bytes(hdr)
        h_int = int.from_bytes(h, byteorder="big")
        tries += 1
        if h_int <= target:
            elapsed = time.time() - start
            return {
                "nonce": nonce,
                "hash_hex": h.hex(),
                "hash_int": h_int,
                "tries": tries,
                "elapsed_s": elapsed
            }
        if show_progress and (nonce & 0xFFFF) == 0 and nonce != 0:
            print(f"tried {nonce} nonces...")

    return None

# Set up a toy header and mine it.
hdr = SimpleBitcoinHeader(
    version=2,
    prev_hash="00"*32,                    # pretend previous hash is all zeros
    merkle_root="11"*32,                  # pretend merkle root is 0x1111...
    timestamp=int(time.time()),
    bits_difficulty_hex_zeros=4           # require 4 leading hex zeros -> similar to "0000........"
)

result = mine(hdr, max_nonce=2_000_000)
if result:
    print("Found valid nonce!")
    print(f"Nonce: {result['nonce']}")
    print(f"Hash: {result['hash_hex']}")
    print(f"Tries: {result['tries']}, Time: {result['elapsed_s']:.4f}s")
else:
    print("No valid nonce found in given range. Try increasing max_nonce or lower difficulty.")