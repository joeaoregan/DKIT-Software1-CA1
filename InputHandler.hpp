/*
    Input handler
    20/10/2022

    Using singleton pattern so it only exists once in the program
*/

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

    void update();
    void close();
    bool isKeyDown(int key);
    bool isKeyDownDelay(int key); // delay for menu 200ms items

private:
    InputHandler() {} // constructor, private for singleton pattern

    static InputHandler *s_pInstance; // Singleton instance of input handler
};