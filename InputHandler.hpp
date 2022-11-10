/*
    Input handler
    20/10/2022

    Using singleton pattern so it only exists once in the program
*/

#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

const bool DELAY = true; // use delay between button presses

class InputHandler
{
public:
    ~InputHandler() {} // deconstructor

    static InputHandler *Instance()
    {
        if (s_pInstance == 0) // if there is no instance handler already
        {
            s_pInstance = new InputHandler(); // create a new one
            return s_pInstance;               // return it
        }
        return s_pInstance; // otherwise return the existing one
    }

    void update() {} // todo
    void close() {}  // todo
    bool isKeyDown(int key);
    bool isKeyDownDelay(int key); // delay for menu 200ms items

    bool select(bool delay = false); // action button - select/fire etc.
    bool left(bool delay = false);   // move left
    bool right(bool delay = false);  // move right
    bool up(bool delay = false);     // move up
    bool down(bool delay = false);   // move down

private:
    InputHandler() {} // constructor, private for singleton pattern

    static InputHandler *s_pInstance; // Singleton instance of input handler
};
#endif

typedef InputHandler Input; // Just can't be bothered typing InputHandler every time
