// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*
    This is an example illustrating the use of the kkmeans object
    and spectral_cluster() routine from the dlib C++ Library.

    The kkmeans object is an implementation of a kernelized k-means clustering
    algorithm.  It is implemented by using the kcentroid object to represent
    each center found by the usual k-means clustering algorithm.

    So this object allows you to perform non-linear clustering in the same way
    a svm classifier finds non-linear decision surfaces.

    This example will make points from 3 classes and perform kernelized k-means
    clustering on those points.  It will also do the same thing using spectral
    clustering.

    The classes are as follows:
        - points very close to the origin
        - points on the circle of radius 10 around the origin
        - points that are on a circle of radius 4 but not around the origin at all
*/

#include <iostream>
#include <vector>

#include <dlib/clustering.h>
#include <dlib/rand.h>

#include <fstream>

using namespace std;
using namespace dlib;

int main()
{
    typedef matrix<double,2,1> sample_type;
    typedef radial_basis_kernel<sample_type> kernel_type;

    kcentroid<kernel_type> kc(kernel_type(0.1),0.01, 8);

    kkmeans<kernel_type> test(kc);

    std::vector<sample_type> samples;
    std::vector<sample_type> initial_centers;

    sample_type m;
    for(std::string line; std::getline(std::cin, line);){
        auto pos_x = line.find(';');
        auto pos_y = line.find('\n', pos_x + 1);
        m(0) = std::stod(line.substr(0, pos_x));
        m(1) = std::stod(line.substr(pos_x + 1 , pos_y ));
        samples.emplace_back(m);
    }

    size_t cluster_num = 3; // TODO:
    test.set_number_of_centers(cluster_num);

    pick_initial_centers(cluster_num, initial_centers, samples, test.get_kernel());

    test.train(samples,initial_centers);

    for(auto const& sample: samples){
        std::cout << sample(0) << ";" << sample(1) << ";cluster" << test(sample) + 1 << std::endl;
    }

    return 0;
}



