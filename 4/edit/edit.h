#include <string>
#include <list>

class TextEditor {
public:
    TextEditor();
    void addText(const std::string& text);
    void deleteText(int length);
    void moveCursor(int steps);
    void copy(int length);
    void paste();
    void print();

private:
    std::list<char> text;       // 用于存储文本内容
    std::list<char>::iterator cursor; // 光标的位置
    std::string clipboard;     // 剪贴板存储复制的内容
};
