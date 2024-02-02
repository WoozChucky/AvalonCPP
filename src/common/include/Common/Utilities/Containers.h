#pragma once

#include <Common/Types.h>

#include <Common/Utilities/Random.h>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace Avalon
{
    template<class T>
    constexpr inline T* AddressOrSelf(T* ptr)
    {
        return ptr;
    }

    template<class T>
    constexpr inline T* AddressOrSelf(T& not_ptr)
    {
        return std::addressof(not_ptr);
    }

    template <class T>
    class CheckedBufferOutputIterator
    {
    public:
        using iterator_category = std::output_iterator_tag;
        using value_type = void;
        using pointer = T*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;

        CheckedBufferOutputIterator(T* buf, size_t n) : _buf(buf), _end(buf + n) {}

        T& operator*() const { check(); return *_buf; }
        CheckedBufferOutputIterator& operator++() { check(); ++_buf; return *this; }
        CheckedBufferOutputIterator operator++(int) { CheckedBufferOutputIterator v = *this; operator++(); return v; }

        [[nodiscard]] size_t remaining() const { return (_end - _buf); }

    private:
        T* _buf;
        T* _end;

        void check() const
        {
            if (!(_buf < _end))
            {
                throw std::out_of_range("index");
            }
        }
    };
}

namespace Avalon::Containers
{
    // resizes <container> to have at most <requestedSize> elements
    // if it has more than <requestedSize> elements, the elements to keep are selected randomly
    template<class C>
    void RandomResize(C& container, std::size_t requestedSize)
    {
        static_assert(std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<typename C::iterator>::iterator_category>::value, "Invalid container passed to Avalon::Containers::RandomResize");

        if (std::size(container) <= requestedSize)
        {
            return;
        }

        auto keepIt = std::begin(container), curIt = std::begin(container);
        U32 elementsToKeep = requestedSize, elementsToProcess = std::size(container);

        while (elementsToProcess)
        {
            // this element has chance (elementsToKeep / elementsToProcess) of being kept
            if (urand(1, elementsToProcess) <= elementsToKeep)
            {
                if (keepIt != curIt)
                {
                    *keepIt = std::move(*curIt);
                }

                ++keepIt;
                --elementsToKeep;
            }

            ++curIt;
            --elementsToProcess;
        }

        container.erase(keepIt, std::end(container));
    }

    template<class C, class Predicate>
    void RandomResize(C& container, Predicate&& predicate, std::size_t requestedSize)
    {
        //! First use predicate filter
        C containerCopy;
        std::copy_if(std::begin(container), std::end(container), std::inserter(containerCopy, std::end(containerCopy)), predicate);

        if (requestedSize)
        {
            RandomResize(containerCopy, requestedSize);
        }

        container = std::move(containerCopy);
    }

    /*
     * Select a random element from a container.
     *
     * Note: container cannot be empty
     */
    template<class C>
    inline auto SelectRandomContainerElement(C const& container) -> typename std::add_const<decltype(*std::begin(container))>::type&
    {
        auto it = std::begin(container);
        std::advance(it, urand(0, uint32(std::size(container)) - 1));
        return *it;
    }

    /*
     * Select a random element from a container.
     *
     * Note: container cannot be empty
     */
    template<class C, class Predicate>
    inline auto SelectRandomContainerElementIf(C const& container, Predicate&& predicate) -> typename std::add_const<decltype(*std::begin(container))>::type&
    {
        C containerCopy;
        std::copy_if(std::begin(container), std::end(container), std::inserter(containerCopy, std::end(containerCopy)), predicate);
        auto it = std::begin(containerCopy);
        std::advance(it, urand(0, uint32(std::size(containerCopy)) - 1));
        return *it;
    }

    /*
     * Select a random element from a container where each element has a different chance to be selected.
     *
     * @param container Container to select an element from
     * @param weights Chances of each element to be selected, must be in the same order as elements in container.
     *                Caller is responsible for checking that sum of all weights is greater than 0.
     *
     * Note: container cannot be empty
     */
    template<class C>
    inline auto SelectRandomWeightedContainerElement(C const& container, std::vector<double> weights) -> decltype(std::begin(container))
    {
        auto it = std::begin(container);
        std::advance(it, urandweighted(weights.size(), weights.data()));
        return it;
    }

    /*
     * Select a random element from a container where each element has a different chance to be selected.
     *
     * @param container Container to select an element from
     * @param weightExtractor Function retrieving chance of each element in container, expected to take an element of the container and returning a double
     *
     * Note: container cannot be empty
     */
    template<class C, class Fn>
    auto SelectRandomWeightedContainerElement(C const& container, Fn weightExtractor) -> decltype(std::begin(container))
    {
        std::vector<double> weights;
        weights.reserve(std::size(container));
        double weightSum = 0.0;

        for (auto& val : container)
        {
            double weight = weightExtractor(val);
            weights.push_back(weight);
            weightSum += weight;
        }

        if (weightSum <= 0.0)
        {
            weights.assign(std::size(container), 1.0);
        }

        return SelectRandomWeightedContainerElement(container, weights);
    }

    /**
     * Returns a pointer to mapped value (or the value itself if map stores pointers)
     */
    template<class M>
    inline auto MapGetValuePtr(M& map, typename M::key_type const& key) -> decltype(AddressOrSelf(map.find(key)->second))
    {
        auto itr = map.find(key);
        return itr != map.end() ? AddressOrSelf(itr->second) : nullptr;
    }

    template<class C>
    inline void RandomShuffle(C& container)
    {
        std::shuffle(std::begin(container), std::end(container), RandomEngine::Instance());
    }

    template<class K, class V, template<class, class, class...> class M, class... Rest>
    void MultimapErasePair(M<K, V, Rest...>& multimap, K const& key, V const& value)
    {
        auto range = multimap.equal_range(key);
        for (auto itr = range.first; itr != range.second;)
        {
            if (itr->second == value)
            {
                itr = multimap.erase(itr);
            }
            else
            {
                ++itr;
            }
        }
    }

    template <typename Container, typename Predicate>
    std::enable_if_t<std::is_move_assignable_v<decltype(*std::declval<Container>().begin())>, void> EraseIf(Container& c, Predicate p)
    {
        auto wpos = c.begin();
        for (auto rpos = c.begin(), end = c.end(); rpos != end; ++rpos)
        {
            if (!p(*rpos))
            {
                if (rpos != wpos)
                {
                    std::swap(*rpos, *wpos);
                }
                ++wpos;
            }
        }
        c.erase(wpos, c.end());
    }

    template <typename Container, typename Predicate>
    std::enable_if_t<!std::is_move_assignable_v<decltype(*std::declval<Container>().begin())>, void> EraseIf(Container& c, Predicate p)
    {
        for (auto it = c.begin(); it != c.end();)
        {
            if (p(*it))
            {
                it = c.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}
