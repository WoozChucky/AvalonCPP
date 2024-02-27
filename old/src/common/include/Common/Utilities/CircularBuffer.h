#pragma once

#include <mutex>
#include <vector>

class CircularBuffer {
public:
    CircularBuffer(size_t size) : _buffer(size), _head(0), _tail(0), _isFull(false) {}
    ~CircularBuffer() {
        _buffer.clear();
    }

    size_t Size() const {
        return _buffer.size();
    }

    bool IsEmpty() const {
        std::lock_guard<std::mutex> lock(_mutex);
        return (!_isFull && (_head == _tail));
    }

    bool IsFull() const {
        std::lock_guard<std::mutex> lock(_mutex);
        return _isFull;
    }

    void Write(char value) {
        std::lock_guard<std::mutex> lock(_mutex);
        WriteInternal(value);
    }

    void Write(std::vector<char>& values) {
        std::lock_guard<std::mutex> lock(_mutex);
        for (const auto& value : values) {
            WriteInternal(value);
        }
    }

    char Read() {
        std::lock_guard<std::mutex> lock(_mutex);
        return ReadInternal();
    }

    std::vector<char> Read(size_t count) {
        std::lock_guard<std::mutex> lock(_mutex);
        std::vector<char> values;
        values.reserve(count);
        while (count-- > 0 && !_isFull) {
            values.push_back(ReadInternal());
        }
        return values;
    }

private:
    void WriteInternal(char value) {
        _buffer[_head] = value;
        if (_isFull) {
            _tail = (_tail + 1) % _buffer.size();
        }
        _head = (_head + 1) % _buffer.size();
        _isFull = (_head == _tail);
    }

    char ReadInternal() {
        if (!_isFull && (_head == _tail)) {
            return -1;
        }
        char value = _buffer[_tail];
        _isFull = false;
        _tail = (_tail + 1) % _buffer.size();
        return value;
    }

    std::vector<char> _buffer;
    size_t _head;
    size_t _tail;
    bool _isFull;
    mutable std::mutex _mutex;
};
