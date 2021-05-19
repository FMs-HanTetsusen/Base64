/* a very fast way to convert
 * both ASCII 8 bit char and Base64 6 bit char
 * to each other using union
 */ 
union base64
{
    struct 
    {
        // this order should not be changed since most CPUs use little-endian (LE)
        unsigned int c : 8;
        unsigned int b : 8;
        unsigned int a : 8;
    }ascii;
    struct 
    {
        // this order should not be changed since most CPUs use little-endian (LE)
        unsigned int d : 6;
        unsigned int c : 6;
        unsigned int b : 6;
        unsigned int a : 6;
    }base64;
};