#include "edit.h"
#include <iostream>
#include <algorithm>

TextEditor::TextEditor() {
    cursor = text.begin(); // 初始化光标位置为文本开头
}

void TextEditor::addText(const std::string& textToAdd) {
    for (char c : textToAdd) {
        cursor = text.insert(cursor, c); // 在光标处插入字符
        ++cursor; // 移动光标到新字符的右侧
    }
}

void TextEditor::deleteText(int length) {
    for (int i = 0; i < length && cursor != text.begin(); ++i) {
        cursor = text.erase(std::prev(cursor)); // 删除光标左侧字符
    }
}

void TextEditor::moveCursor(int steps) {
    if (steps > 0) {
        while (steps-- > 0 && cursor != text.end()) {
            ++cursor; // 光标向右移动
        }
    } else {
        while (steps++ < 0 && cursor != text.begin()) {
            --cursor; // 光标向左移动
        }
    }
}

void TextEditor::copy(int length) {
    clipboard.clear();
    auto it = cursor;
    for (int i = 0; i < length && it != text.begin(); ++i) {
        --it; // 从光标左侧开始倒退
        clipboard += *it;
    }
    std::reverse(clipboard.begin(), clipboard.end()); // 恢复正确顺序
}

void TextEditor::paste() {
    for (char c : clipboard) {
        cursor = text.insert(cursor, c); // 在光标处插入剪贴板内容
        ++cursor;
    }
}

void TextEditor::print() {
    for (char c : text) {
        std::cout << c;
    }
    std::cout << std::endl;
}
