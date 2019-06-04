/* 
 * Define a struct suitable for representing a playing card. 
 */
typedef struct
{
  int value;
  enum {spades, hearts, diamonds, clubs} suit;
} cards;