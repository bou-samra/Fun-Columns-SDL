/*********************************
 ** ASCII spritemap X/Y coords **
 *********************************
// Black X,Y, White X,Y

int ascii [128][4] = {
{518, 49, 582, 49}, // NUL Null
{518, 49, 582, 49}, // SOH Start Of Heading
{518, 49, 582, 49}, // STX Start of TeXt
{518, 49, 582, 49}, // ETX End of TeXt
{518, 49, 582, 49}, // EOT End Of Transm,
{518, 49, 582, 49}, // ENQ ENQuiry
{518, 49, 582, 49}, // ACK ACKnowledge
{518, 49, 582, 49}, // BEL BELl
{518, 49, 582, 49}, // BS Back Space
{518, 49, 582, 49}, // HT Horizontal Tabulation (Character Tabulation)
{518, 49, 582, 49}, // LF Line Feed
{518, 49, 582, 49}, // VT Vertical Tabulation (Line Tabulation)
{518, 49, 582, 49}, // FF Form Feed
{518, 49, 582, 49}, // CR Carriage Return
{518, 49, 582, 49}, // SO Shift Out
{518, 49, 582, 49}, // SI Shift In
{518, 49, 582, 49}, // DLE Data Link Escape
{518, 49, 582, 49}, // DC1 Device Control 1
{518, 49, 582, 49}, // DC2 Device Control 2
{518, 49, 582, 49}, // DC3 Device Control 3
{518, 49, 582, 49}, // DC4 Device Control 4
{518, 49, 582, 49}, // NAK Negative AKnowledgement
{518, 49, 582, 49}, // SYN SYNchronous idle
{518, 49, 582, 49}, // ETB End of Transmission Block
{518, 49, 582, 49}, // CAN CANcel
{518, 49, 582, 49}, // EM End of Medium
{518, 49, 582, 49}, // SUB SUBstitute
{518, 49, 582, 49}, // ESC ESCape
{518, 49, 582, 49}, // FS File Separator
{518, 49, 582, 49}, // GS Group Separator
{518, 49, 582, 49}, // RS Record Separator
{518, 49, 582, 49}, // US Unit Separator
{518, 49, 582, 49}, // SPC Space 510, 574
{494, 25, 558, 25}, // ! Exclamation mark (point)
{486, 37, 550, 37}, // " Quotation mark, quotes
{510, 43, 574, 43}, // # Number sign, hash
{502, 25, 566, 25}, // $ Dollar Sign
{510, 25, 574, 25}, // % Percent sign
{486, 49, 550, 49}, // & Ampersand
{494, 37, 558, 37}, // ' Apostrophe
{470, 31, 534, 31}, // ( Left parenthesis
{478, 31, 542, 31}, // ) Right parenthesis
{462, 31, 526, 31}, // * Asterisk
{502, 31, 566, 31}, // + Plus sign
{486, 43, 550, 43}, // , Comma
{486, 31, 550, 31}, // - Hyphen, dash, minus
{478, 43, 542, 43}, // . Full stop, dot, point
{518, 37, 582, 37}, // / Forward slash
{478, 19, 542, 19}, // 0 zero
{486, 19, 550, 19}, // 1 one
{494, 19, 558, 19}, // 2 two
{502, 19, 566, 19}, // 3 three
{510, 19, 574, 19}, // 4 four
{518, 19, 582, 19}, // 5 five
{462, 25, 526, 25}, // 6 six
{470, 25, 534, 25}, // 7 seven
{478, 25, 542, 25}, // 8 eight
{486, 25, 550, 25}, // 9 nine
{470, 37, 534, 37}, // : Colon
{478, 37, 542, 37}, // ; Semicolon
{462, 43, 526, 43}, // < Less than, Left angled bracket
{510, 31, 574, 31}, // = Equal
{470, 43, 534, 43}, // > Greater than, Right angled bracket
{478, 49, 542, 49}, // ? Question mark
{518, 43, 582, 43}, // @ At sign, commercial at
{462, 1, 526, 1}, // A Alpha
{470, 1, 534, 1}, // B Bravo
{478, 1, 542, 1}, // C Charlie
{486, 1, 550, 1}, // D Delta
{494, 1, 558, 1}, // E Echo
{502, 1, 566, 1}, // F Foxtrot
{510, 1, 574, 1}, // G Golf
{518, 1, 582, 1}, // H Hotel
{462, 7, 526, 7}, // I India
{470, 7, 534, 7}, // J Juliett
{478, 7, 542, 7}, // K Kilo
{486, 7, 550, 7}, // L Lima
{494, 7, 558, 7}, // M Mike
{502, 7, 566, 7}, // N November
{510, 7, 574, 7}, // O Oscar
{518, 7, 582, 7}, // P Papa
{462, 13, 526, 13}, // Q Quebec
{470, 13, 534, 13}, // R Romeo
{478, 13, 542, 13}, // S Sierra
{486, 13, 550, 13}, // T Tango
{494, 13, 558, 13}, // U Uniform
{502, 13, 566, 13}, // V Victor
{510, 13, 574, 13}, // W Whiskey
{518, 13, 582, 13}, // X X-ray
{462, 19, 526, 19}, // Y Yankee
{470, 19, 534, 19}, // Z Zulu
{518, 31, 582, 31}, // [ Left square bracket
{510, 37, 574, 37}, // \ Backslash
{462, 37, 526, 37}, // ] Right square bracket
{518, 25, 582, 25}, // ^ Circumflex accent, Caret
{494, 31, 558, 31}, // _ Underscore
{502, 43, 566, 43}, // ` Grave accent
{462, 1, 526, 1}, // a alpha
{470, 1, 534, 1}, // b bravo
{478, 1, 542, 1}, // c charlie
{486, 1, 550, 1}, // d delta
{494, 1, 558, 1}, // e echo
{502, 1, 566, 1}, // f foxtrot
{510, 1, 574, 1}, // g golf
{518, 1, 582, 1}, // h hotel
{462, 7, 526, 7}, // i india
{470, 7, 534, 7}, // j juliett
{478, 7, 542, 7}, // k kilo
{486, 7, 550, 7}, // l lima
{494, 7, 558, 7}, // m mike
{502, 7, 566, 7}, // n november
{510, 7, 574, 7}, // o oscar
{518, 7, 582, 7}, // p papa
{462, 13, 526, 13}, // q quebec
{470, 13, 534, 13}, // r romeo
{478, 13, 542, 13}, // s seirra
{486, 13, 550, 13}, // t tango
{494, 13, 558, 13}, // u uniform
{502, 13, 566, 13}, // v victor
{510, 13, 574, 13}, // w whiskey
{518, 13, 582, 13}, // x x-ray
{462, 19, 526, 19}, // y yankee
{470, 19, 534, 19}, // z zulu
{462, 49, 526, 49}, // { Left curly bracket
{502, 37, 566, 37}, // | Vertical bar
{470, 49, 534, 49}, // } Right curly bracket
{494, 43, 558, 43}, // ~ Tilde
{518, 49, 582, 49}, // DEL DELete
};
