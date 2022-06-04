#ifndef ENGINE_CORE_INPUT_SCANCODE_INCLUDED
#define ENGINE_CORE_INPUT_SCANCODE_INCLUDED

namespace Engine::Core::Input
{
    /**
     * The following enum is pretty much copied from SDL2 and matches the type `SDL_Scancode`.
     * Its values are based on the USB usage page standard:
     * https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
     *
     * In case another input implementation must be supported (glfw, WinAPI ...),
     * a constexpr mapping function could be written to map values from this enum to another.
     */
    enum class ScanCode : int
    {
        Unknown = 0,

        /**
         *  \name Usage page 0x07
         *
         *  These values are from usage page 0x07 (USB keyboard page).
         */
        /* @{ */

        A = 4,
        B = 5,
        C = 6,
        D = 7,
        E = 8,
        F = 9,
        G = 10,
        H = 11,
        I = 12,
        J = 13,
        K = 14,
        L = 15,
        M = 16,
        N = 17,
        O = 18,
        P = 19,
        Q = 20,
        R = 21,
        S = 22,
        T = 23,
        U = 24,
        V = 25,
        W = 26,
        X = 27,
        Y = 28,
        Z = 29,

        One = 30,
        Two = 31,
        Three = 32,
        Four = 33,
        Five = 34,
        Six = 35,
        Seven = 36,
        Eight = 37,
        Nine = 38,
        Zero = 39,

        Return = 40,
        Escape = 41,
        Backspace = 42,
        Tab = 43,
        Space = 44,

        Minus = 45,
        Equals = 46,
        LeftBracket = 47,
        RightBracket = 48,
        Backslash = 49, /**< Located at the lower left of the return
                                    *   key on ISO keyboards and at the right end
                                    *   of the QWERTY row on ANSI keyboards.
                                    *   Produces Reverse Solidus (backslash) and
                                    *   Vertical Line in a Us layout, Reverse
                                    *   Solidus and Vertical Line in a Uk Mac
                                    *   layout, Number Sign and Tilde in a Uk
                                    *   Windows layout, Dollar Sign and Pound Sign
                                    *   in a Swiss German layout, Number Sign and
                                    *   Apostrophe in a German layout, Grave
                                    *   Accent and Pound Sign in a French Mac
                                    *   layout, and Asterisk and Micro Sign in a
                                    *   French Windows layout.
                                    */
        NonUSHash = 50, /**< ISO USB keyboards actually use this code
                                    *   instead of 49 for the same key, but all
                                    *   Oses I've seen treat the two codes
                                    *   identically. So, as an implementor, unless
                                    *   your keyboard generates both of those
                                    *   codes and your Os treats them differently,
                                    *   you should generate Backslash
                                    *   instead of this code. As a user, you
                                    *   should not rely on this code because Sdl
                                    *   will never generate it with most (all?)
                                    *   keyboards.
                                    */
        Semicolon = 51,
        Apostrophe = 52,
        Grave = 53, /**< Located in the top left corner (on both ANSI
                                *   and ISO keyboards). Produces Grave Accent and
                                *   Tilde in a Us Windows layout and in Us and Uk
                                *   Mac layouts on ANSI keyboards, Grave Accent
                                *   and Not Sign in a Uk Windows layout, Section
                                *   Sign and Plus-Minus Sign in Us and Uk Mac
                                *   layouts on ISO keyboards, Section Sign and
                                *   Degree Sign in a Swiss German layout (Mac:
                                *   only on ISO keyboards), Circumflex Accent and
                                *   Degree Sign in a German layout (Mac: only on
                                *   ISO keyboards), Superscript Two and Tilde in a
                                *   French Windows layout, Commercial At and
                                *   Number Sign in a French Mac layout on ISO
                                *   keyboards, and Less-Than Sign and Greater-Than
                                *   Sign in a Swiss German, German, or French Mac
                                *   layout on ANSI keyboards.
                                */
        Comma = 54,
        Period = 55,
        Slash = 56,

        CapsLock = 57,

        F1 = 58,
        F2 = 59,
        F3 = 60,
        F4 = 61,
        F5 = 62,
        F6 = 63,
        F7 = 64,
        F8 = 65,
        F9 = 66,
        F10 = 67,
        F11 = 68,
        F12 = 69,

        PrintScreen = 70,
        ScrollLock = 71,
        Pause = 72,
        Insert = 73, /**< Insert on PC, Help on some Mac keyboards
                          (but does send code 73, not 117) */
        Home = 74,
        PageUp = 75,
        Delete = 76,
        End = 77,
        PageDown = 78,
        Right = 79,
        Left = 80,
        Down = 81,
        Up = 82,

        NumLockClear = 83, /**< Num Lock on PC, Clear on Mac keyboards */
        KPDivide = 84,
        KPMultiply = 85,
        KPMinus = 86,
        KPPlus = 87,
        KPEnter = 88,
        KP1 = 89,
        KP2 = 90,
        KP3 = 91,
        KP4 = 92,
        KP5 = 93,
        KP6 = 94,
        KP7 = 95,
        KP8 = 96,
        KP9 = 97,
        KP0 = 98,
        KPPeriod = 99,

        NonUSBackslash = 100, /**< This is the additional key that ISO
                               *   keyboards have over ANSI ones,
                               *   located between left shift and Y.
                               *   Produces Grave Accent and Tilde in a
                               *   US or UK Mac layout, Reverse Solidus
                               *   (backslash) and Vertical Line in a
                               *   US or UK Windows layout, and
                               *   Less-Than Sign and Greater-Than Sign
                               *   in a Swiss German, German, or French
                               *   layout. */
        Application = 101, /**< Windows Contextual Menu, compose */
        Power = 102, /**< The USB document says this is a status flag,
                      *   not a physical key - but some Mac keyboards
                      *   do have a power key. */
        Kp_Equals = 103,
        F13 = 104,
        F14 = 105,
        F15 = 106,
        F16 = 107,
        F17 = 108,
        F18 = 109,
        F19 = 110,
        F20 = 111,
        F21 = 112,
        F22 = 113,
        F23 = 114,
        F24 = 115,
        Execute = 116,
        Help = 117,
        Menu = 118,
        Select = 119,
        Stop = 120,
        Again = 121, /**< Redo */
        Undo = 122,
        Cut = 123,
        Copy = 124,
        Paste = 125,
        Find = 126,
        Mute = 127,
        VolumeUp = 128,
        VolumeDown = 129,
    /* not sure whether there's a reason to enable these */
    /*     LockingCapsLock = 130,  */
    /*     LockingNumLock = 131, */
    /*     LockingScrollLock = 132, */
        KPComma = 133,
        KPEqualsAS400 = 134,

        International1 = 135, /**< Used on Asian keyboards, see footnotes in USB doc */
        International2 = 136,
        International3 = 137, /**< Yen */
        International4 = 138,
        International5 = 139,
        International6 = 140,
        International7 = 141,
        International8 = 142,
        International9 = 143,
        Lang1 = 144, /**< Hangul/English toggle */
        Lang2 = 145, /**< Hanja conversion */
        Lang3 = 146, /**< Katakana */
        Lang4 = 147, /**< Hiragana */
        Lang5 = 148, /**< Zenkaku/Hankaku */
        Lang6 = 149, /**< reserved */
        Lang7 = 150, /**< reserved */
        Lang8 = 151, /**< reserved */
        Lang9 = 152, /**< reserved */

        AltErase = 153, /**< Erase-Eaze */
        SysReq = 154,
        Cancel = 155,
        Clear = 156,
        Prior = 157,
        Return2 = 158,
        Separator = 159,
        Out = 160,
        Oper = 161,
        ClearAgain = 162,
        CrSel = 163,
        ExSel = 164,

        KP00 = 176,
        KP000 = 177,
        ThousandsSeparator = 178,
        DecimalSeparator = 179,
        CurrencyUnit = 180,
        CurrencySubunit = 181,
        KPLeftParen = 182,
        KPRightParen = 183,
        KPLeftBrace = 184,
        KPRightBrace = 185,
        KPTab = 186,
        KPBackspace = 187,
        KPA = 188,
        KPB = 189,
        KPC = 190,
        KPD = 191,
        KPE = 192,
        KPF = 193,
        KPXOR = 194,
        KPPower = 195,
        KPPercent = 196,
        KPLess = 197,
        KPGreater = 198,
        KPAmpersand = 199,
        KPDBLAmpersand = 200,
        KPVerticalBar = 201,
        KPDBLVerticalBar = 202,
        KPColon = 203,
        KPHash = 204,
        KPSpace = 205,
        KPAt = 206,
        KPExclam = 207,
        KPMemStore = 208,
        KPMemRecall = 209,
        KPMemClear = 210,
        KPMemAdd = 211,
        KPMemSubtract = 212,
        KPMemMultiply = 213,
        KPMemDivide = 214,
        KPPlusMinus = 215,
        KPClear = 216,
        KPClearEntry = 217,
        KPBinary = 218,
        KPOctal = 219,
        KPDecimal = 220,
        KPHexadecimal = 221,

        LCTRL = 224,
        LSHIFT = 225,
        LALT = 226, /**< Alt, Option */
        LGUI = 227, /**< Windows, Command (Apple), Meta */
        RCTRL = 228,
        RSHIFT = 229,
        RALT = 230, /**< Alt Gr, Option */
        RGUI = 231, /**< Windows, Command (Apple), Meta */

        Mode = 257,    /**< I'm not sure if this is really not covered
                        *   by any of the above, but since there's a
                        *   special KMod_Mode for it I'm adding it here
                        */

        /* @} *//* Usage page 0x07 */

        /**
         *  \name Usage page 0x0C
         *
         *  These values are mapped from usage page 0x0C (USB consumer page).
         */
        /* @{ */

        AudioNext = 258,
        AudioPrev = 259,
        AudioStop = 260,
        AudioPlay = 261,
        AudioMute = 262,
        MediaSelect = 263,
        WWW = 264,
        Mail = 265,
        Calculator = 266,
        Computer = 267,
        ACSearch = 268,
        ACHome = 269,
        ACBack = 270,
        ACForward = 271,
        ACStop = 272,
        ACRefresh = 273,
        ACBookmarks = 274,

        /* @} *//* Usage page 0x0C */

        /**
         *  \name Walther keys
         *
         *  These are values that Christian Walther added (for Mac keyboard?).
         */
        /* @{ */

        BrightnessDown = 275,
        BrightnessUp = 276,
        DisplaySwitch = 277, /**< Display mirroring/dual display switch,
                              *   video mode switch */
        KBDIllumToggle = 278,
        KBDIllumDown = 279,
        KBDIllumUp = 280,
        Eject = 281,
        Sleep = 282,

        App1 = 283,
        App2 = 284,

        /* @} *//* Walther keys */

        /**
         *  \name Usage page 0x0C (additional media keys)
         *
         *  These values are mapped from usage page 0x0C (USB consumer page).
         */
        /* @{ */

        AudioRewind = 285,
        AudioFastForward = 286,

        /* @} *//* Usage page 0x0C (additional media keys) */

        /* Add any other keys here. */

        NumScanCodes = 512 /**< Not a key, just marks the number of scancodes
                            *   for array bounds */
    };

    /**
     * `ScanCode::NumScanCodes` as `size_t`, for example to be used in
     * template parameter lists of container types so you don't have to static_cast there.
     */
    constexpr size_t NumScanCodes = static_cast<size_t>(ScanCode::NumScanCodes);

    /**
     * \returns Pointer to the name of the scancode.
     * If the scancode doesn't have a name, this function returns an empty string.
     */
    const char* GetScanCodeName(ScanCode scanCode);
}

#endif