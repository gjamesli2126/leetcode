#include <bits/stdc++.h>
using namespace std;

/// A small table that maps any byte (0..255) to its bit‐reversed counterpart.
static const uint8_t BIT_REV_TABLE[256] = [](){
    uint8_t table[256];
    for (int i = 0; i < 256; i++) {
        uint8_t v = (uint8_t)i, r = 0;
        for (int b = 0; b < 8; b++) {
            r = (uint8_t)((r << 1) | (v & 1));
            v >>= 1;
        }
        table[i] = r;
    }
    return vector<uint8_t>(table, table + 256);
}();

/**
 * reverseBitsEveryRow:
 *   - filename: path to an existing binary file
 *   - rowLenBytes: how many bytes each “row” occupies on disk
 *   - rowLenBits:   how many bits in that row we actually want to reverse;
 *                   must satisfy 0 < rowLenBits <= 8*rowLenBytes
 *
 * Returns true on success, false on any I/O error or invalid arguments.
 */
bool reverseBitsEveryRow(const string& filename,
                         size_t rowLenBytes,
                         size_t rowLenBits)
{
    if (rowLenBits > rowLenBytes * 8) return false;

    fstream file(filename, ios::in | ios::out | ios::binary);
    if (!file.is_open()) return false;

    // 1) Find total file size
    file.seekg(0, ios::end);
    size_t totalSize = (size_t)file.tellg();
    if (totalSize % rowLenBytes != 0) {
        file.close();
        return false;  // not a whole number of rows
    }
    size_t numRows = totalSize / rowLenBytes;

    vector<uint8_t> buffer(rowLenBytes);

    for (size_t row = 0; row < numRows; row++) {
        // 2) Read one row
        file.seekg((streamoff)(row * rowLenBytes), ios::beg);
        file.read(reinterpret_cast<char*>(buffer.data()), rowLenBytes);
        if (!file.good()) {
            file.close();
            return false;
        }

        // 3a) Reverse byte order
        for (size_t i = 0; i < rowLenBytes/2; i++) {
            swap(buffer[i], buffer[rowLenBytes - 1 - i]);
        }

        // 3b) Reverse bits inside each full byte in that row
        size_t fullBytes = rowLenBits / 8;
        for (size_t i = 0; i < fullBytes; i++) {
            buffer[i] = BIT_REV_TABLE[ buffer[i] ];
        }
        // If there are leftover bits (< 8) in the last partial byte
        size_t leftover = rowLenBits % 8;
        if (leftover > 0) {
            // Reverse that byte fully, then zero out the unused low bits.
            uint8_t x = buffer[fullBytes];
            uint8_t r = BIT_REV_TABLE[x];
            uint8_t mask = (uint8_t)(0xFF << (8 - leftover));
            buffer[fullBytes] = (uint8_t)(r & mask);
        }

        // 4) Write the row back in‐place
        file.seekp((streamoff)(row * rowLenBytes), ios::beg);
        file.write(reinterpret_cast<const char*>(buffer.data()), rowLenBytes);
        if (!file.good()) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

// ---------------------------------------------
// (Optional) Demo for reverseBitsEveryRow
// ---------------------------------------------
int main() {
    // Create a tiny file with 3 rows × 2 bytes each:
    //   Row0 = 0x0001  (bits: 0000 0000 0000 0001) → reversed: 1000 0000 0000 0000 = 0x8000
    //   Row1 = 0xAAC7  (bits: 1010 1010 1100 0111) → reversed: 1110 0011 0101 0101 = 0xE355
    //   Row2 = 0xF03C  (bits: 1111 0000 0011 1100) → reversed: 0011 1100 0000 1111 = 0x3C0F
    const string tempFile = "test_rows.bin";
    {
        ofstream out(tempFile, ios::binary | ios::trunc);
        if (!out.is_open()) {
            cerr << "Cannot create " << tempFile << "\n";
            return 1;
        }
        uint16_t data[3] = { 0x0001, 0xAAC7, 0xF03C };
        for (int i = 0; i < 3; i++) {
            uint16_t v = data[i];
            // Write little‐endian: low byte first
            out.put((char)(v & 0xFF));
            out.put((char)((v >> 8) & 0xFF));
        }
        out.close();
        cout << "Created “" << tempFile << "” with 3 rows.\n";
    }

    // Call our function (each row = 2 bytes, each row = 16 bits)
    if (!reverseBitsEveryRow(tempFile, /*rowLenBytes=*/2, /*rowLenBits=*/16)) {
        cerr << "reverseBitsEveryRow failed\n";
        return 2;
    }
    cout << "Reversal complete.\n";

    // Read back and print each 16-bit row in hex:
    ifstream in(tempFile, ios::binary);
    if (!in.is_open()) {
        cerr << "Cannot reopen file\n";
        return 3;
    }
    cout << "After reversal:\n";
    for (int i = 0; i < 3; i++) {
        uint8_t lo, hi;
        in.read(reinterpret_cast<char*>(&lo), 1);
        in.read(reinterpret_cast<char*>(&hi), 1);
        uint16_t combined = (uint16_t)lo | (uint16_t(hi) << 8);
        cout << "  Row " << i << " = 0x"
             << hex << setw(4) << setfill('0') << combined << dec << "\n";
    }
    in.close();

    cout << "Expected:\n"
         << "  Row0 → 0x8000\n"
         << "  Row1 → 0xE355\n"
         << "  Row2 → 0x3C0F\n";
    return 0;
}