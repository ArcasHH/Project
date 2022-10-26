#ifndef POINT_H
#define POINT_H

struct Point {
    int x = 0;
    int y = 0;
};

enum class Type {
    Point,
    Hit,
    FieldStatus
};

enum class Result {
    Hit,
    Kill,
    Miss
};

struct Packet {
    Point P{};
    Result Hit{};
    Type PacketTy = Type::FieldStatus;

    Packet(Point P_in) : P{P_in}, PacketTy{Type::Point} {}
    Packet(Result Hit_in) : Hit{Hit_in}, PacketTy{Type::Hit} {}
    Packet() = default;

    char *getRaw() { return reinterpret_cast<char *>(this); }
    char const *getRaw() const { return reinterpret_cast<char const *>(this); }
    int getSize() const { return sizeof(Packet); }
};

#endif // POINT_H
