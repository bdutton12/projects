#include "course.cpp"
#include "vehicle.cpp"
#include <string>
#include <iostream>
#include <sstream>

std::string GetLayout() {
    std::string layout;
    std::string line;

    std::cout << "\"S\" - Start point" << std::endl;
    std::cout << "\"F\" - Finish point" << std::endl;
    std::cout << "\"*\" - On-track (Asphalt)" << std::endl;
    std::cout << "\".\" - Off-track (Grass)" << std::endl;
    std::cout << "Enter track line by line, enter \"q\" on new line when done:" << std::endl << std::endl;

    //Loop until blank line entered then return string that represents track layout
    while(line != "q\n") {
        layout += line;
        line = "";
        std::cin >> line;
        line.push_back('\n');
    }

    return layout;
}

int main() {
    std::string track_layout = GetLayout();

    Course c1(track_layout);
    std::cout << c1;

    return 0;
}