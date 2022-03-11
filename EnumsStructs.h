#ifndef ENUMSSTRUCTS_H
#define ENUMSSTRUCTS_H

enum NegativeFreq {
    Always = 1,
    Sometimes = 0,
    Never = -1
};

enum DialogSettingsMode {
    AmountInstanceMode = 0,
    LowestNoMode = 1,
    HighestNoMode = 2,
    AfterDecimalMode = -1
};

enum ActionFlags {
    Multiplication = 1ull << 1,
    Division = 1ull << 2,
    Addition = 1ull << 3,
    Subtraction = 1ull << 4
};

#endif // ENUMSSTRUCTS_H
