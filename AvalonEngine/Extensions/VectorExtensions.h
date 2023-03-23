//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_VECTOREXTENSIONS_H
#define AVALONENGINE_VECTOREXTENSIONS_H

#include <vector>

namespace av
{

    class VectorExtensions
    {
    public:

        template <class T, class Y>
        static void RemoveElements(std::vector<T>& vec, std::vector<Y> index)
        {
            for (auto it = index.begin(); it != index.end(); it++)
            {
                vec.erase(vec.begin() + static_cast<int>(*it));
            }
        }
    };

}

#endif //AVALONENGINE_VECTOREXTENSIONS_H
