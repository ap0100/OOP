#include <iostream>
using namespace std;

class Folder;

class File {
    protected:
        string name;
        Folder *parent;

    public:
        File() : name(""), parent(nullptr) {};

        File(const string &s, Folder *f) : name(s), parent(f) {};

        virtual double file_size()=0;

        string get_name() {
            return this->name;
        }

        void set_name(const string &s){
            this->name=s;
        }

        void add_parent(Folder *folder){
            this->parent=folder;
        }

        virtual ~File() {};
};

enum Encodings {
    UTF8,
    ASCII
};

class textFile : public File {
    Encodings encoding;
    int numchars;

    public:
        textFile(Encodings e, int n_c, const string &s) : encoding(e), numchars(n_c) {
           // this->name=s;
           this->set_name(s);
        };

        double file_size() override {
            if(this->encoding==UTF8) return (double)((this->numchars)*1.5);
            else return this->numchars;
        }
};

class otherFile : public File {
    double bytesize;

    public:
        otherFile(double b_s, const string &s) : bytesize(b_s) {
            this->name=s;
        };

        double file_size() override {
            return this->bytesize;
        }
};

class imageFile : public File {
    int width;
    int height;
    int compressed;

    public:
        imageFile(int w, int h, int cmpr, const string &s) : width(w), height(h), compressed(cmpr) {
            this->name=s;
        };

        double file_size() override {
            return (this->width)*(this->height)*(this->compressed);
        }
};


class Folder {
    File **files;
    Folder **folders;
    Folder *parent;
    int num_files;
    int num_folders;

    public:
        Folder() : files(nullptr), folders(nullptr), parent(nullptr), num_files(0), num_folders(0) {};

        void operator+=(File *file){
            this->num_files++;

            File **new_files=new File*[this->num_files];
            for(int i=0; i<this->num_files; i++) new_files[i]=this->files[i];
            new_files[this->num_files-1]=file;

            delete [] this->files;
            this->files=new_files;
        }

        File* operator[](const string &filename){
            for(int i=0; i<this->num_files; i++) if(this->files[i]->get_name()==filename) return this->files[i];
            return nullptr;
        }

        double folder_size(){
            double res=0;

            for(int i=0; i<this->num_folders; i++)
                for(int j=0; j<this->num_files; j++)
                    res+=this->folders[i]->files[j]->file_size();

            return res;
        }

        ~Folder(){
            delete [] files;
            delete [] folders;
        }
};


int main(){
    Folder folder;
    textFile *txt = new textFile(UTF8, 1000, "textfile.txt");
    otherFile *other = new otherFile(500, "otherfile.dat");
    imageFile *img = new imageFile(800, 600, 2, "imagefile.jpg");

    folder+=txt;
    folder+=other;
    folder+=img;

    string filename="imagefile.jpg";
    File* foundFile=folder[filename];

    delete txt;
    delete other;
    delete img;

    return 0;
}