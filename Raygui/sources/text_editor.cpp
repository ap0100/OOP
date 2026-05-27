#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <bits/stdc++.h>
using namespace std;

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

    while (!WindowShouldClose()) {
        BeginDrawing();

        //writing and editing text
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

        if (IsKeyPressedRepeat(KEY_BACKSPACE) || IsKeyPressed(KEY_BACKSPACE)){
            if (cursor>0) {
                for (int i=cursor-1; i<letter_count; i++) text[i]=text[i+1];
                cursor--;
                letter_count--;
                text[letter_count]='\0';
            }
        }

        Vector2 text_size=MeasureTextEx(font, text, 18, 0.7f);

        if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) if (cursor>0) cursor--;
        if (IsKeyPressedRepeat(KEY_RIGHT) || IsKeyPressed(KEY_RIGHT)) if (static_cast<float>(cursor+1)<text_size.x)  cursor++;

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
                int col=cursor-current_line_start,
                prev_line_end=current_line_start-1,
                prev_line_start=get_line_start(text, prev_line_end);

                int prev_line_length=prev_line_end-prev_line_start;

                cursor=prev_line_start+min(col, prev_line_length);
            }
        }

        if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
            int current_line_end=get_line_end(text, cursor, letter_count);

            if (current_line_end<letter_count) {
                int current_line_start=get_line_start(text, cursor),
                col=cursor-current_line_start,
                next_line_start=current_line_end+1;

                int next_line_end=get_line_end(text, next_line_start, letter_count),
                next_line_length=next_line_end-next_line_start;

                cursor=next_line_start + min(col, next_line_length);
            }
        }

        //basic setup
        ClearBackground({242, 250, 232, 255});
        DrawTextEx(font, "Text editor started", {10.0f, 10.0f}, 24, 0.7, {217, 40, 9, 255});
        DrawLineEx({10.0f, 38.0f}, {static_cast<float>(GetScreenWidth()-10), 38.0f}, 3.0f, {217, 140, 9, 255});

        //draw text
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

        //cursor
        string before_cursor="";
        float row_of_cursor=0;
        for (int i=0; i<cursor; i++) {
            if (text[i]=='\n') {
                row_of_cursor++;
                before_cursor.clear();
            }else before_cursor+=text[i];
        }

        if (static_cast<int>(GetTime()*1.6)%2){
            /*Vector2 text_size=MeasureTextEx(font, text, 18, 0.7f);
            DrawLineEx({(10.0f+text_size.x)+3, 52.0f}, {(text_size.x+10.0f)+3, 75.0f}, 3.5f, {121, 204, 6, 255});
            */
            Vector2 size=MeasureTextEx(font, before_cursor.c_str(), 18, 0.7f);
            DrawLineEx({10.0f+size.x, 52.0f+(row_of_cursor*line_height)}, {10.0f+size.x, 75.0f+(row_of_cursor*line_height)}, 3.5f, {121, 204, 6, 255});
        }

        EndDrawing();
    }

    CloseWindow();


    return 0;
}