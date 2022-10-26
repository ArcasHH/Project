#ifndef SHAREDDEATA_H
#define SHAREDDEATA_H

// This class is passed through UDP pachage to exchange IPs.
struct SharedData {
    // TODO validate Port and add hash.
    int Port;
    int Turn;

    char *getRaw() { return reinterpret_cast<char *>(this); }
    char const *getRaw() const { return reinterpret_cast<char const*>(this); }

    static int getSize() { return sizeof(SharedData); }
};

#endif // SHAREDDEATA_H
