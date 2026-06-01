#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

void save_to_file(const char* filename, const char* text, int len) {
    ofstream file(filename);
    if (file.is_open()) {
        file.write(text, len);
        file.close();
    }
}

int load_from_file(const char* filename, char* buffer, int max_size) {
    ifstream file(filename);
    if (!file.is_open()) return 0;

    file.seekg(0, ios::end);
    size_t size=file.tellg();
    if (size>=max_size) size=max_size-1;
    file.seekg(0, ios::beg);

    file.read(buffer, size);
    buffer[size]='\0';
    file.close();
    return static_cast<int>(size);
}


int get_line_start(char txt[], int pos) {
    while (pos>0 && txt[pos-1]!='\n') pos--;
    return pos;
}

int get_line_end(char txt[], int pos, int len) {
    while (pos<len && txt[pos]!='\n') pos++;
    return pos;
}


int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1000, 700, "Simple_Text-Editor");

    Font font=LoadFont("../resources/fonts/TypeWriterInked-Regular.ttf");
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    SetTargetFPS(60);

    char text[4096]={0};
    int letter_count=0, cursor=0;
    float line_height=25.0f;

    Rectangle saveBtn={ 380, 8, 80, 20 };
    Rectangle openBtn={ 470, 8, 80, 20 };
    string status_msg="";
    double status_time=0.0;
    const char* file_path="../resources/document.txt";

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            if (IsKeyPressed(KEY_S)) {
                save_to_file(file_path, text, letter_count);
                status_msg="Saved!";
                status_time=GetTime();
            }
            if (IsKeyPressed(KEY_O)) {
                int new_len=load_from_file(file_path, text, sizeof(text));
                if (new_len>0) {
                    letter_count=new_len;
                    cursor=min(cursor, letter_count);
                    status_msg="Opened!";
                }else status_msg="Open failed - file not found";
                status_time=GetTime();
            }
        }


        int key=GetCharPressed();
        while (key>0) {
            if (key>=32 && key<=125) {
                for (int i=letter_count; i>cursor; i--) text[i]=text[i-1];
                text[cursor]=static_cast<char>(key);
                cursor++;
                letter_count++;
                text[letter_count]='\0';
            }
            key=GetCharPressed();
        }

        if (IsKeyPressedRepeat(KEY_BACKSPACE) || IsKeyPressed(KEY_BACKSPACE)) {
            if (cursor>0) {
                for (int i=cursor-1; i<letter_count; i++) text[i]=text[i+1];
                cursor--;
                letter_count--;
                text[letter_count]='\0';
            }
        }

        if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) if (cursor > 0) cursor--;
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) if (cursor < letter_count) cursor++;

        if (IsKeyPressedRepeat(KEY_ENTER) || IsKeyPressed(KEY_ENTER)) {
            for (int i=letter_count; i>cursor; i--) text[i]=text[i-1];
            text[cursor]='\n';
            cursor++;
            letter_count++;
            text[letter_count]='\0';
        }

        if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) {
            int current_line_start=get_line_start(text, cursor);
            if (current_line_start>0) {
                int col=cursor-current_line_start;
                int prev_line_end=current_line_start-1;
                int prev_line_start=get_line_start(text, prev_line_end);
                int prev_line_length=prev_line_end-prev_line_start;
                cursor=prev_line_start+min(col, prev_line_length);
            }
        }

        if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
            int current_line_end=get_line_end(text, cursor, letter_count);
            if (current_line_end<letter_count) {
                int current_line_start=get_line_start(text, cursor);
                int col=cursor-current_line_start;
                int next_line_start=current_line_end+1;
                int next_line_end=get_line_end(text, next_line_start, letter_count);
                int next_line_length=next_line_end-next_line_start;
                cursor=next_line_start+min(col, next_line_length);
            }
        }

        BeginDrawing();
        ClearBackground({242, 250, 232, 255});
        DrawTextEx(font, "Text editor started", {10.0f, 10.0f}, 24, 0.7f, {217, 40, 9, 255});
        DrawLineEx({10.0f, 38.0f}, {static_cast<float>(GetScreenWidth() - 10), 38.0f}, 3.0f, {217, 140, 9, 255});


        if (GuiButton(saveBtn, "Save")) {
            save_to_file(file_path, text, letter_count);
            status_msg="Saved!";
            status_time=GetTime();
        }

        if (GuiButton(openBtn, "Open")) {
            int new_len=load_from_file(file_path, text, sizeof(text));
            if (new_len>0) {
                letter_count=new_len;
                cursor=min(cursor, letter_count);
                status_msg="Opened!";
            }else status_msg="Open failed - file not found";
            status_time=GetTime();
        }

        if ((GetTime()-status_time)<2.0)
            DrawTextEx(font, status_msg.c_str(), {580, 10}, 16, 0.7f, {80, 80, 80, 255});


        string line="";
        float y=55.0f;
        for (int i=0; i<letter_count; i++) {
            if (text[i]=='\n') {
                DrawTextEx(font, line.c_str(), {10.0f, y}, 18, 0.7f, {45, 54, 35, 255});
                y+=line_height;
                line.clear();
            }else line+=text[i];
        }
        DrawTextEx(font, line.c_str(), {10.0f, y}, 18, 0.7f, {45, 54, 35, 255});


        string before_cursor="";
        float row_of_cursor=0;
        for (int i=0; i<cursor; i++) {
            if (text[i]=='\n') {
                row_of_cursor++;
                before_cursor.clear();
            }else before_cursor +=text[i];
        }

        if (static_cast<int>(GetTime()*1.6)%2) {
            Vector2 cursor_pos=MeasureTextEx(font, before_cursor.c_str(), 18, 0.7f);
            float cursor_x=10.0f + cursor_pos.x;
            float cursor_y_top=55.0f+row_of_cursor*line_height;
            float cursor_y_bottom=cursor_y_top + 18.0f;
            DrawLineEx({cursor_x, cursor_y_top}, {cursor_x, cursor_y_bottom}, 3.5f, {121, 204, 6, 255});
        }

        EndDrawing();
    }

    CloseWindow();


    return 0;
}