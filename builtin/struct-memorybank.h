//    Memory Bank

    {"reservebank",     basReserveBank,     2,  0},
    {"baseimage",       basBaseImage,       2,  0},
    {"baseimagecc",     basBaseImageCC,     2,  0},
    {"basescreen",      basBaseScreen,      2,  0},
    {"basesound",       basBaseSound,       2,  0},

    {"freebase",        basFreeBase,        1,  0},
    {"freebank",        basFreeBank,        1,  0},

    {"copybank",        basCopyBank,        2,  0},
    {"loadbank",        basLoadBank,        1,  1},
    {"savebank",        basSaveBank,        1,  1},

    {"setbank",         basSetBank,         0,  1},
    {"currentbank",     basSetBank,         0,  1},
    {"sizebank",        basSizeBank,        0,  1},
    {"banksize",        basSizeBank,        0,  1},

    {"poke",            basPoke,            2,  1},
    {"doke",            basDoke,            2,  1},
    {"loke",            basLoke,            2,  1},

    {"peek",            basPeek,            1,  1},
    {"deek",            basDeek,            1,  1},
    {"leek",            basLeek,            1,  1},

    {"memcopy",         basMemCopy,         5,  0},
