// Songs_file.cpp : 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

struct Songs
{
    string title;
    string author;
    string year;
    string text[10];
};

void ToFile_one_thing(FILE* any_file, char any_char[], string any_list)
{
    getline(cin, any_list);
    strcpy(any_char, any_list.c_str());
    fputs(any_char, any_file);
    fputs("\n", any_file);
}

void ToFile_(FILE* any_file, char any_char[], string any_list)
{
    
    strcpy(any_char, any_list.c_str());
    fputs(any_char, any_file);
}

void Display_all(FILE* any_file, char any_char[])
{
    while (!feof(any_file))
    {
        fgets(any_char, 30, any_file);

        cout << " " << any_char << endl;
    }
}

short int Count_lines(FILE* any_file, char any_char[])
{
    short int count = 0;

    while (!feof(any_file))
    {
        fgets(any_char, 30, any_file);
        count++;
    }
    return count;
}

string Display_one_thing(FILE* any_file, char any_char[])
{
    string any_list;
    fgets(any_char, 30, any_file);
    any_list = string(any_char);
    cout << " " << any_list << endl;
    return any_list;
}



int main()
{
    int const size = 1; //количество песен
    string any_string;
    char any_too[30];
    Songs song_list[size];
    bool yes = 0;
    short int 
        line_number = 0,
        any_size = 1,
        choice,
        delete_text,
        edit_text;

    Songs* SongList(NULL); //= new Songs[any_size];

    
    FILE* songs_list;
    
    do {

        cout << " 1 - Add new song " << endl;
        cout << " 2 - Display all songs " << endl;
        cout << " 3 - Delete the song text " << endl;
        cout << " 4 - Edit the song text " << endl;
        cout << " 5 - Delete all songs " << endl;
        cout << " 0 - Finish " << endl;
        cout << " ";
        cin >> choice;
        cin.ignore();

    
        switch (choice)
        {
            case 1:
                if (fopen_s(&songs_list, "songs.txt", "a") != NULL)
                {
                    cout << "File could not be created!";
                }
                else
                {
                    for (int i = 0; i < size; i++)
                    {
                        cout << "\n\n";
                        cout << " What is title?\n ";
                        ToFile_one_thing(songs_list, any_too, song_list[i].title);

                        cout << " Who is author?\n ";
                        ToFile_one_thing(songs_list, any_too, song_list[i].author);

                        cout << " When the song was written (year)?\n ";
                        ToFile_one_thing(songs_list, any_too, song_list[i].year);

                        cout << " What is the text of the song?\n ";
                        for (int j = 0; j < 10; j++)
                        {
                            ToFile_one_thing(songs_list, any_too, song_list[i].text[j]);
                        }

                    }

                    fclose(songs_list);
                }

                break;

            case 2:
                if (fopen_s(&songs_list, "songs.txt", "r") != NULL)
                {
                    cout << "File could not be created!";
                }
                else
                {
                    while (!feof(songs_list))
                    {
                        Display_all(songs_list, any_too);
                    }
                    fclose(songs_list);
                }
                break;

            case 3:
                // считаю количество строк
            
                if (fopen_s(&songs_list, "songs.txt", "r") != NULL)
                {
                    cout << "File could not be created!";
                }
                else
                {
                    any_size = Count_lines(songs_list, any_too) / 13;
                    cout << " The Number of songs is " << any_size - 1 << endl;
                }
                fclose(songs_list);


                SongList = new Songs[any_size];
               
                if (fopen_s(&songs_list, "songs.txt", "r") != NULL)
                {
                    cout << "File could not be created!";
                }
                else
                {
                    for (int i = 0; i < any_size; i++)
                    {
                        cout << " #" << i + 1 << endl;
                        cout << " The title " << endl;
                        SongList[i].title = Display_one_thing(songs_list, any_too);
                         
                        cout << " The author " << endl;
                        SongList[i].author = Display_one_thing(songs_list, any_too);
                        //cout << "* >>" << SongList[i].author << endl;

                        cout << " The year " << endl;
                        SongList[i].year = Display_one_thing(songs_list, any_too);
                        //cout << "* >>" << SongList[i].year << endl;

                        cout << " The text " << endl;
                        for (int j = 0; j < 10; j++)
                        {
                            SongList[i].text[j] = Display_one_thing(songs_list, any_too);
                            //cout << "* >>" << SongList[i].text[j] << endl;
                        }
                    }
                 fclose(songs_list);
                }
               
               //без защиты от дурака
                cout << " Enter the number of the song whose text you want to delete " << endl;
                cin >> delete_text;
                delete_text--;
                //cout << " delete_text >>> " << delete_text << endl;
                //cin.ignore();

                if (fopen_s(&songs_list, "songs.txt", "w") != NULL)
                {
                    cout << "File could not be created!";
                }
                else
                {
                    for (int i = 0; i < any_size; i++)
                    {
                        any_string = SongList[i].title;
                        ToFile_(songs_list, any_too, any_string);

                        any_string = SongList[i].author;
                        ToFile_(songs_list, any_too, any_string);

                        any_string = SongList[i].year;
                        ToFile_(songs_list, any_too, any_string);
                 
                        if (i == delete_text)
                        {
                            for (int j = 0; j < 10; j++)
                            {
                                any_string = "\n";
                                ToFile_(songs_list, any_too, any_string);
                            }
                        } 
                        else if (i != delete_text)
                        {
                            for (int j = 0; j < 10; j++)
                            {
                                
                                any_string = SongList[i].text[j];
                                ToFile_(songs_list, any_too, any_string);
                            }
                        }
                    
                    }
                    fclose(songs_list);
                }
                delete[]SongList;
                
                break;

            case 4:
                if (fopen_s(&songs_list, "songs.txt", "r") != NULL)
                {
                    cout << "File could not be created!";
                }
                else
                {
                    any_size = Count_lines(songs_list, any_too) / 13;
                    cout << " The Number of songs is " << any_size - 1 << endl;
                }
                fclose(songs_list);

                SongList = new Songs[any_size];

                if (fopen_s(&songs_list, "songs.txt", "r") != NULL)
                {
                    cout << "File could not be created!";
                }
                else
                {
                    for (int i = 0; i < any_size; i++)
                    {
                        cout << " #" << i + 1 << endl;
                        cout << " The title " << endl;
                        SongList[i].title = Display_one_thing(songs_list, any_too);

                        cout << " The author " << endl;
                        SongList[i].author = Display_one_thing(songs_list, any_too);
                        //cout << "* >>" << SongList[i].author << endl;

                        cout << " The year " << endl;
                        SongList[i].year = Display_one_thing(songs_list, any_too);
                        //cout << "* >>" << SongList[i].year << endl;

                        cout << " The text " << endl;
                        for (int j = 0; j < 10; j++)
                        {
                            cout << " #" << j + 1;
                            SongList[i].text[j] = Display_one_thing(songs_list, any_too);
                            //cout << "* >>" << SongList[i].text[j] << endl;
                        }
                    }
                    fclose(songs_list);
                }
                cout << " Enter the number of the song whose text you want to edit " << endl;
                cin >> delete_text;
                delete_text--;

                cout << " Enter the number of the line you want to edit " << endl;
                cin >> edit_text;
                edit_text--;

                cin.ignore();
                cout << " Enter new string " << endl;
                getline(cin, any_string);
                SongList[delete_text].text[edit_text] = any_string;

                if (fopen_s(&songs_list, "songs.txt", "w") != NULL)
                {
                    cout << "File could not be created!";
                }
                else
                {
                    for (int i = 0; i < any_size; i++)
                    {
                        any_string = SongList[i].title;
                        ToFile_(songs_list, any_too, any_string);

                        any_string = SongList[i].author;
                        ToFile_(songs_list, any_too, any_string);

                        any_string = SongList[i].year;
                        ToFile_(songs_list, any_too, any_string);

                            for (int j = 0; j < 10; j++)
                            {
                               any_string = SongList[i].text[j];
                               ToFile_(songs_list, any_too, any_string);
                            }
                    }
                    fclose(songs_list);
                }
                delete[]SongList;
                break;

            case 5:
                if (fopen_s(&songs_list, "songs.txt", "w") != NULL)
                {
                    cout << "File could not be created!";
                }
                else
                {
                   fputc(' ', songs_list);
                   fclose(songs_list);
                }
                break;

            default:
                break;
        }
    } while (choice != 0);
   
    //delete[]SongList;
}
