#include <iostream>
#include <vector>

#include <dlib/clustering.h>
#include <dlib/rand.h>

#include <fstream>

using namespace std;
using namespace dlib;

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Неверное число параметров\nФормат вызова: kkmeans <n>" << std::endl;
        return 1;
    }

    std::string str_clusters_num = argv[1];
    if (!std::all_of(str_clusters_num.begin(), str_clusters_num.end(), ::isdigit)) {
        std::cerr << "Параметр <n> должен быть типа int" << std::endl;
        return 1;
    }

    size_t cluster_num = std::stoull(str_clusters_num);
    if (cluster_num == 0) {
        std::cerr << "Параметр <n> должен быть больше нуля." << std::endl;
        return 1;
    }

    typedef matrix<double, 2, 1>             sample_type;
    typedef radial_basis_kernel<sample_type> kernel_type;

    kcentroid<kernel_type> kc(kernel_type(0.0001), 0.1, 8);

    kkmeans<kernel_type> test(kc);

    std::vector<sample_type> samples;
    std::vector<sample_type> initial_centers;

    sample_type      m;
    for (std::string line; std::getline(std::cin, line);) {
        auto pos_x = line.find(';');
        auto pos_y = line.find('\n', pos_x + 1);
        m(0) = std::stod(line.substr(0, pos_x));
        m(1) = std::stod(line.substr(pos_x + 1, pos_y));
        samples.emplace_back(m);
    }

    test.set_number_of_centers(cluster_num);

    pick_initial_centers(cluster_num, initial_centers, samples, test.get_kernel());

    test.train(samples, initial_centers);

    for (auto const &sample: samples) {
        std::cout << sample(0) << ";" << sample(1) << ";cluster" << test(sample) + 1 << std::endl;
    }
    return 0;
}



