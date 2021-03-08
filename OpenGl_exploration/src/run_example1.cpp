#include <example1.h>

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);

    example_1::Example1 example_1_obj;
    
    if(!example_1_obj.run()){
        LOG(FATAL) << "Errors encountered!";
    }

    return 0;
}