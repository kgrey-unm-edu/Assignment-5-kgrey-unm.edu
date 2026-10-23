#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "pixel.h"

void average_colors(std::vector<Pixel> &pixel_list);
void flip_vertically(std::vector<Pixel> &pixel_list);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " pixels.dat\n";
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream fin(filename);

    if (!fin)
    {
        std::cout << "Error opening file.\n";
        return 1;
    }

    std::vector<Pixel> pixel_list;

    std::string line;

    while (std::getline(fin, line))
    {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);

        Pixel p;

        p.x = std::stoi(line.substr(0, pos1));

        p.y = std::stoi(
            line.substr(pos1 + 1,
                        pos2 - pos1 - 1));

        p.r = std::stof(
            line.substr(pos2 + 1,
                        pos3 - pos2 - 1));

        p.g = std::stof(
            line.substr(pos3 + 1,
                        pos4 - pos3 - 1));

        p.b = std::stof(
            line.substr(pos4 + 1));

        pixel_list.push_back(p);
    }

    fin.close();

    std::cout << "Pixels loaded: "
              << pixel_list.size()
              << std::endl;

    average_colors(pixel_list);

    flip_vertically(pixel_list);

    std::ofstream fout("flipped.dat");

    for (const auto &p : pixel_list)
    {
        fout << p.x << ","
             << p.y << ","
             << p.r << ","
             << p.g << ","
             << p.b << "\n";
    }

    fout.close();

    std::cout << "Flipped image written to flipped.dat\n";

    return 0;
}

void average_colors(std::vector<Pixel> &pixel_list)
{
    double total_r = 0.0;
    double total_g = 0.0;
    double total_b = 0.0;

    for (const auto &p : pixel_list)
    {
        total_r += p.r;
        total_g += p.g;
        total_b += p.b;
    }

    double count = pixel_list.size();

    std::cout << "Average R: "
              << total_r / count
              << std::endl;

    std::cout << "Average G: "
              << total_g / count
              << std::endl;

    std::cout << "Average B: "
              << total_b / count
              << std::endl;
}

void flip_vertically(std::vector<Pixel> &pixel_list)
{
    const int HEIGHT = 256;

    for (auto &p : pixel_list)
    {
        p.y = (HEIGHT - 1) - p.y;
    }
}
