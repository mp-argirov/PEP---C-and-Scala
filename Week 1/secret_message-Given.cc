// A message is hidden by moving every letter a fixed number of places along the alphabet.
// Move every letter back by the same number of places, and the words can be read again.
// Here the readable words are called the plain words, and the moved ones the hidden words.
// The message is kept in a vector of characters.
// cout does not know how to print a vector, so this file prints one character at a time.
// This file does not give new meanings to operators such as << or ==.
//
// This file compiles and runs as it is.
// It prints a broken poster and FAIL lines, because your functions are not written yet.
// Two of the checks pass already, but only by chance.
// Each task is marked with the word TODO.
// Do them in order, from stage 1 to stage 7, and compile and run after each one.
// Aim for about 90 minutes.
// The stretch at the end is optional.
//
// Compile and run with these two commands:
//   g++ -std=c++11 -Wall -Wextra -Wpedantic -o secret_message secret_message.cc
//   ./secret_message

#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::string;
using std::vector;
using std::stoi;

// ============================================================================
// GIVEN. These two small helper functions are used by the checks in the main function.
// You do not need to change them.
// ============================================================================

// Prints PASS or FAIL, then a few words saying what was checked.
void check(const string & label, bool ok)
{
    cout << (ok ? "PASS  " : "FAIL  ") << label << "\n";
}

// Turns a vector of characters back into a string, so that a check can compare it with text.
string text_of(const vector<char> & v) {
    string s;
    int n = v.size();
    for (int i = 0; i < n; ++i)
    {
        s = s + v[i];
    }
    return s;
}

// ============================================================================
// STAGE 1. One letter. (10 minutes)
// ============================================================================

// TODO 1. The function is given a character called c and a number called by.
// Move c forward along the alphabet by that many places, and return the letter you land on.
// We've covered that in the lecture
//
// If c is not a lower-case letter, return it unchanged.

// For example, spaces, commas and capital letters all stay as they are.
// Keep the sum of c and by in an int, not in a char.
// A C++ char is smaller than a Java char, so the sum may not fit in it.
// If the sum has gone past 'z', take 26 off it.
// That wraps it round to the start of the alphabet.
char shift_letter(char c, int by)
{
    vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int is_in_lowercase_alphabet = 0;
    int num_equivalent;
    for (int i = 0; i < 26; ++i)
    {
        if (c == alphabet[i])
        {
            is_in_lowercase_alphabet = 1;
            num_equivalent = i;
        }
    }
    if (is_in_lowercase_alphabet == 0)
    {
        return c;
    }
    num_equivalent = num_equivalent + by;
    while (num_equivalent > 25)
    {
        num_equivalent -= 26;
    }
    char real_letter = alphabet[num_equivalent];
    return real_letter;
}

// ============================================================================
// STAGE 2. The message as a vector, and printing it. (15 minutes)
// ============================================================================

// TODO 2a. Go through the string called text, one character at a time, from first to last.
// Add each character to the end of the vector v with push_back, so that the order is kept.
vector<char> to_chars(const string & text)
{
    vector<char> v;
    for (char c : text)
    {
        v.push_back(c);
    }
    return v;
}

// TODO 2b. Print every character in the vector, one after another.
// Put no spaces between them, and no new line at the end.
// You cannot write cout << v, because cout does not know how to print a vector.
// So print the characters yourself, one at a time.
void print_chars(const vector<char> & v)
{
    for (char c : v)
    {
        cout << c;
    }
}

// ============================================================================
// STAGES 3, 4 AND 5. The same loop, written three times. (10 minutes each)
// Each time, the vector is passed into the function in a different way.
// ============================================================================

// TODO 3. Here v is passed by value, so v is a copy of the caller's vector.
// Go through v and replace each element with what shift_letter returns for it.
// Then return v.
// The caller's own vector is left as it was, because you only changed the copy.
vector<char> encode_by_value(vector<char> v, int by)
{
    for (int i = 0; i < v.size(); ++i)
    {
        char character = v[i];
        v[i] = shift_letter(character, by);
    }
    return v;

}

// TODO 4. Here v is passed by reference, so v is the caller's own vector, not a copy.
// Write the same loop as in stage 3.
// Now the caller's own vector changes, so there is nothing to return.
void encode_by_ref(vector<char> & v, int by)
{
    for (int i = 0; i < v.size(); ++i)
    {
        char character = v[i];
        v[i] = shift_letter(character, by);
    }
}

// TODO 5. Here v is passed by const reference, so v is the caller's own vector again.
// The word const means you may look at v, but you may not change it.
// So fill the new vector called result instead.
// Go through v and pass each element to shift_letter.
// Add what it returns to the end of the vector result with push_back.
// Then return result.
// If you try to change an element of v in here, the compiler will stop you.
vector<char> encode_by_const_ref(const vector<char> & v, int by)
{
    vector<char> result;
    for (int i = 0; i < v.size(); ++i)
    {
        char character = v[i];
        result.push_back(shift_letter(character, by));
    }
    return result;
}

// GIVEN. To decode, move each letter forward until it has gone all the way round the alphabet.
// A letter moved 3 places and then 23 more has moved 26 places, so it is back where it started.
// That is why this function moves each letter forward by 26 minus the original shift.
// The stretch at the end uses it.
vector<char> decode(const vector<char> & v, int by) {
    return encode_by_const_ref(v, 26 - by);
}

// ============================================================================
// GIVEN. Prints one line of the poster from three loose pieces.
// The pieces are the plain words, the shift and the author's name.
// The hidden words come first, with spaces added to make 35 characters.
// Then come the plain words, with spaces to make 34, and then the author's name.
// It works once stages 1, 2 and 3 are done.
// ============================================================================
void poster_line(const vector<char> & plain, int shift, const string & author) {
    vector<char> hidden = encode_by_value(plain, shift);
    print_chars(hidden);
    for (int i = hidden.size(); i < 35; ++i) { cout << " "; }
    print_chars(plain);
    for (int i = plain.size(); i < 34; ++i) { cout << " "; }
    cout << "from " << author << "\n";
}

// ============================================================================
// STAGE 6. A class. (20 minutes)
// ============================================================================

// GIVEN. Read this class, but do not change it.
// Author has no default constructor, meaning no constructor that takes no arguments.
// So every new Author needs a name, or another Author to copy.
class Author {
private:
    string name;
public:
    Author(const string & name_in) : name(name_in) { }
    const string & get_name() const { return name; }
};

class Message {
private:
    vector<char> plain;     // the plain words, one character per element
    int shift;              // how many places each letter moves
    Author from;            // a whole Author, stored inside the Message, not a reference to one

public:
    // TODO 6a. Finish the initialiser list, which is the part after the colon.
    // Put the member called plain at the front of the list.
    // Make it by passing the parameter called text to the function to_chars.
    // Then give the member called shift the value of the parameter shift_in, instead of 0.
    // Keep the list in the same order as the members above, or the compiler will warn you.
    // The member that holds the author is already in the list.
    // It has to be set in the list, because Author has no default constructor.
    // Setting it inside the braces instead, as you would in Java, would not compile.
    // See slides 22 to 24.
    Message(const string & text, int shift_in, const Author & from_in)
        : shift(0), from(from_in) {
        (void) text;        // Delete these two lines once the list is complete.
        (void) shift_in;
    }

    // GIVEN. Each of these three methods has the word const after its round brackets.
    // That const is a promise that the method does not change the object.
    // See slides 45 to 48.
    const vector<char> & get_plain() const { return plain; }
    int get_shift() const { return shift; }
    const Author & get_author() const { return from; }

    // TODO 6b. Store the number n as the message's new shift.
    void set_shift(int n) {
        (void) n;           // Replace this line with your code.
    }

    // TODO 6c. Return the hidden words.
    // Call encode_by_const_ref with the plain words and this message's own shift.
    // Return what it gives you.
    vector<char> cipher() const {
        return plain;       // Replace this line. For now it returns the plain words.
    }

    // TODO 6d. Print this message as one line of the poster.
    // The line shows the hidden words, then the plain words, then the author's name.
    // The function poster_line above prints exactly that from loose pieces, so call it.
    // The pieces it needs are the plain words, the shift and the author's name.
    void print() const {
        cout << "(print not written)\n";     // Replace this line with your code.
    }
};

// ============================================================================
// STAGE 7. Comparing two messages. (10 minutes)
// The function is outside the class, and it takes both messages by const reference.
// ============================================================================

// TODO 7. Two messages count as the same message when they hold the same plain words.
// Their shifts and authors do not matter.
// Get the plain words of each message with get_plain.
// If the two vectors have different sizes, return false.
// Otherwise compare the two vectors position by position.
// Return false as soon as the characters in the same position are different.
// If you reach the end without finding a difference, return true.
bool same_words(const Message & a, const Message & b) {
    (void) a;               // Replace these three lines with your code.
    (void) b;
    return false;
}

// ============================================================================
// STRETCH. Crack a message without being told its shift. (optional, 15 to 20 minutes)
// ============================================================================

// TODO 8 (optional). Try every shift from 1 to 25.
// Print one line for each shift: the shift, two spaces, then the secret decoded with it.
// One of the 25 lines will read as English, and the shift on that line is the one used.
void crack(const vector<char> & secret) {
    (void) secret;          // Replace this line with your loop.
}

// ============================================================================
// GIVEN. The main function prints the poster twice and runs the checks for stages 1 to 7.
// ============================================================================
int main() {
    cout << "Secret Message\n";
    cout << "--------------\n";

    // First the poster is printed from loose pieces.
    // It works once stages 1, 2 and 3 are done.
    poster_line(to_chars("the treasure is behind the clock"), 3, "Ada");
    poster_line(to_chars("meet me at the pier at midnight"), 7, "Alan");
    poster_line(to_chars("the password is open sesame"), 11, "Ada");
    poster_line(to_chars("bring cake, we have run out"), 21, "Alan");
    cout << "\n";

    check("1: one letter moves along the alphabet", shift_letter('a', 3) == 'd');
    check("1: z wraps round to the start", shift_letter('z', 1) == 'a');
    check("1: a space is not a letter, so it stays put", shift_letter(' ', 5) == ' ');

    check("2: to_chars keeps every character, in order", text_of(to_chars("abc")) == "abc");

    vector<char> plain = to_chars("attack at dawn");
    vector<char> secret = encode_by_value(plain, 5);
    check("3: encode by value made the hidden words", text_of(secret) == "fyyfhp fy ifbs");
    check("3: encode by value left your own vector alone", text_of(plain) == "attack at dawn");

    encode_by_ref(plain, 5);
    check("4: encode by ref changed your own vector", text_of(plain) == "fyyfhp fy ifbs");

    vector<char> words = to_chars("attack at dawn");
    vector<char> hidden = encode_by_const_ref(words, 5);
    check("5: encode by const ref made the hidden words", text_of(hidden) == "fyyfhp fy ifbs");
    check("5: encode by const ref left your own vector alone", text_of(words) == "attack at dawn");

    // Then the same poster is printed again, this time by the Message objects.
    // It works once stage 6 is done.
    cout << "\n";
    Author ada("Ada");
    Author alan("Alan");
    Message m1("the treasure is behind the clock", 3, ada);
    Message m2("meet me at the pier at midnight", 7, alan);
    Message m3("the password is open sesame", 11, ada);
    Message m4("bring cake, we have run out", 21, alan);
    m1.print();
    m2.print();
    m3.print();
    m4.print();
    cout << "\n";

    Message copy = m1;      // copies the whole object, including the Author inside it
    copy.set_shift(9);
    check("6: changing the copy left the original alone", m1.get_shift() == 3 && copy.get_shift() == 9);
    check("6: the cipher uses the message's own shift", text_of(m1.cipher()) == "wkh wuhdvxuh lv ehklqg wkh forfn");

    check("7: same words, different shift, still the same message", same_words(m1, copy));
    check("7: different words are a different message", !same_words(m1, m2));

    cout << "\ncracking ";
    print_chars(m3.cipher());
    cout << "\n";
    crack(m3.cipher());
    return 0;
}
