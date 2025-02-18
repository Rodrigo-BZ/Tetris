/**
 * @file BlocTypes.h
 * @brief Header file for the BlocTypes class. It contains the classes of all 7 Bloc types
 * @version 0.1
 * 
 */
#include "Bloc.h"

class BlocL: public Bloc{
public:
    BlocL(): Bloc(QColor(255,165,0)){ //orange
        forme = {{
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }};
        lenght = 9;
    }
};

class BlocI: public Bloc{
public:
    BlocI(): Bloc(QColor(0,255,255)){ //cyan
        forme = {{
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }};
        lenght = 16;
    }
};

class BlocO: public Bloc{
public:
    BlocO(): Bloc(QColor(255,255,0)){ //yellow
        forme = {{
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }};
        lenght = 4;
    }
};

class BlocT: public Bloc{
public:
    BlocT(): Bloc(QColor(128,0,128)){ //purple
        forme = {{
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }};
        lenght = 9;
    }
};

class BlocJ: public Bloc{
public:
    BlocJ(): Bloc(QColor(0,0,255)){ //blue
        forme = {{
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }};
        lenght = 9;
    }
};

class BlocS: public Bloc{
public:
    BlocS(): Bloc(QColor(0,255,0)){ //green
        forme = {{
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }};
        lenght = 9;
    }
};

class BlocZ: public Bloc{
public:
    BlocZ(): Bloc(QColor(255,0,0)){ //red
        forme = {{
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }};
        lenght = 9;
    }
};
