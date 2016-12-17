#pragma once
#include <vector>

namespace core {
    class network_layout {
    public:
        network_layout()
            : input_(0), output_(0), hidden_(0)
        {}
        network_layout& set_input(const std::size_t size)
        {
            input_ = size;
        }
        network_layout& set_output(const std::size_t size)
        {
            output_ = size;
        }
        network_layout& push_back_hidden(const std::size_t size)
        {
            hidden_.push_back(size);
        }

        std::size_t input() const { return input_; }
        std::size_t output() const { return output_; }
        std::vector<std::size_t> hidden() const { return hidden_; }
    private:
        std::size_t input_;
        std::size_t output_;
        std::vector<std::size_t> hidden_;
    };

}