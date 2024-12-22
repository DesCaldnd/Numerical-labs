//
// Created by Des Caldnd on 9/16/2024.
//

#ifndef NUMEROLOGY_MATRIX_HPP
#define NUMEROLOGY_MATRIX_HPP

#include <vector>
#include <iterator>
#include <exception>
#include <ranges>

namespace Numerology
{
    template <typename T>
    class matrix final
    {
    private:
        using mat_t = std::vector<std::vector<T>>; // vector of columns (for better performance when working with vectors)

        mat_t data;

    public:

        using value_type = T;

        class column_view;
        class row_view;

        class row_view final
        {
        private:
            matrix& _mat;
            const size_t _ind;

        public:

            bool equal_by_address(const row_view& other) const noexcept;

            bool operator==(const row_view& other) const noexcept;
            bool operator==(const column_view& other) const noexcept;

            size_t size() const noexcept;

            T& operator[](size_t ind); // Trows exception if out of bound

            row_view& operator=(const std::vector<T>& vec) &;
            row_view& operator=(std::vector<T>&& vec) &;

            row_view& operator=(const row_view& vec) &;
            row_view& operator=(row_view&& vec) &; //Moves each object

            row_view& operator=(const column_view& vec) &;
            row_view& operator=(column_view&& vec) &; //Moves each object

            row_view& operator+=(const row_view& other) &;
            row_view& operator+=(const column_view& other) &;

            row_view& operator-=(const row_view& other) &;
            row_view& operator-=(const column_view& other) &;

            T operator*=(const row_view& other);
            T operator*=(const column_view& other);

            row_view& operator*=(T other) &;
            row_view& operator/=(T other) &;

            void swap(row_view other);

            row_view(matrix& mat, size_t ind) noexcept;

            class reverse_iterator;

            class iterator final
            {
            private:

                row_view _row;
                size_t _ind;

            public:
                using difference_type = std::ptrdiff_t;
                using value_type = T;
                using pointer = T*;
                using reference = T&;
                using iterator_category = std::random_access_iterator_tag;

                iterator(const row_view& row, size_t ind = 0) noexcept;
                operator reverse_iterator() noexcept;

                iterator& operator+=(size_t count) & noexcept;
                iterator operator+(size_t count) const noexcept;
                iterator& operator++() & noexcept;
                iterator operator++(int) noexcept;

                iterator& operator-=(size_t count) & noexcept;
                iterator operator-(size_t count) const noexcept;
                iterator& operator--() & noexcept;
                iterator operator--(int) noexcept;

                std::ptrdiff_t operator-(const iterator& it)const noexcept;

                reference operator*() noexcept;
                pointer operator->() noexcept;

            };

            class reverse_iterator final
            {
            private:

                row_view _row;
                size_t _ind;

            public:
                using difference_type = std::ptrdiff_t;
                using value_type = T;
                using pointer = T*;
                using reference = T&;
                using iterator_category = std::random_access_iterator_tag;

                operator iterator() noexcept;
                reverse_iterator(const row_view& row, size_t ind = 0) noexcept;

                reverse_iterator& operator+=(size_t count) & noexcept;
                reverse_iterator operator+(size_t count) const noexcept;
                reverse_iterator& operator++() & noexcept;
                reverse_iterator operator++(int) noexcept;

                reverse_iterator& operator-=(size_t count) & noexcept;
                reverse_iterator operator-(size_t count) const noexcept;
                reverse_iterator& operator--() & noexcept;
                reverse_iterator operator--(int) noexcept;

                std::ptrdiff_t operator-(const reverse_iterator& it)const noexcept;

                reference operator*() noexcept;
                pointer operator->() noexcept;

            };

            iterator begin() noexcept;
            iterator end() noexcept;
            reverse_iterator rbegin() noexcept;
            reverse_iterator rend() noexcept;
        };

        class column_view final
        {
        public:

            using vector = std::vector<T>;

        private:
            vector& _vec;

        public:

            bool equal_by_address(const column_view& other) const noexcept;

            bool operator==(const row_view& other) const noexcept;
            bool operator==(const column_view& other) const noexcept;

            size_t size() const noexcept;

            T& operator[](size_t ind); // Trows exception if out of bound

            column_view& operator=(const std::vector<T>& vec) &;
            column_view& operator=(std::vector<T>&& vec) &;

            column_view& operator=(const row_view& vec) &;
            column_view& operator=(row_view&& vec) &; //Moves each object

            column_view& operator=(const column_view& vec) &;
            column_view& operator=(column_view&& vec) &; //Moves each object

            column_view& operator+=(const row_view& other) &;
            column_view& operator+=(const column_view& other) &;

            column_view& operator-=(const row_view& other) &;
            column_view& operator-=(const column_view& other) &;

            T operator*=(const row_view& other);
            T operator*=(const column_view& other);

            column_view& operator*=(T other) &;
            column_view& operator/=(T other) &;

            void swap(column_view other);

            column_view(vector& vec) noexcept;

            vector::iterator begin() noexcept;
            vector::iterator end() noexcept;
            vector::reverse_iterator rbegin() noexcept;
            vector::reverse_iterator rend() noexcept;
        };

        static matrix identity(size_t size);
        static matrix as_matrix_row(const std::vector<size_t>& vec);
        static matrix as_matrix_row(std::vector<size_t>&& vec);
        static matrix as_matrix_row(row_view vec);
        static matrix as_matrix_row(column_view vec);

        static matrix as_matrix_column(const std::vector<size_t>& vec);
        static matrix as_matrix_column(std::vector<size_t>&& vec);
        static matrix as_matrix_column(row_view vec);
        static matrix as_matrix_column(column_view vec);

        T& operator[](size_t row, size_t column);
        row_view operator[](size_t row);
        row_view get_row(size_t row);
        column_view get_column(size_t column);

        matrix() =default;
        matrix(size_t row_count, size_t column_count, const T& value);

        bool operator==(const matrix& other) noexcept;

        matrix& operator+=(const matrix& other) &;
        matrix operator+(const matrix& other);

        matrix& operator-=(const matrix& other) &;
        matrix operator-(const matrix& other);

        matrix& operator*=(const matrix& other) &;
        matrix operator*(const matrix& other);
        matrix& operator*=(const T& other) &;
        matrix operator*(const T& other);

        matrix& operator/=(const T& other) &;
        matrix operator/(const T& other);

        size_t row_count() const noexcept;
        size_t column_count() const noexcept;

        void set_row_count(size_t c, const T& val);
        void set_column_count(size_t c, const T& val);

        matrix& invert() &;
        matrix inverse();

        void swap_rows(size_t f, size_t r);
        void swap_columns(size_t f, size_t r);

        T det();

        matrix minor(size_t r, size_t c);

        matrix& transpose() &;
        matrix transposed();

        class row_reverse_iterator;

        class row_iterator final
        {
        private:

            matrix& _mat;
            size_t index;

        public:
            using difference_type = std::ptrdiff_t;
            using value_type = row_view;
            using pointer = row_view*;
            using reference = row_view&;
            using iterator_category = std::random_access_iterator_tag;

            row_iterator(matrix& mat, size_t ind = 0) noexcept;
            operator row_reverse_iterator() noexcept;

            row_iterator& operator+=(size_t count) & noexcept;
            row_iterator operator+(size_t count) const noexcept;
            row_iterator& operator++() & noexcept;
            row_iterator operator++(int) noexcept;

            row_iterator& operator-=(size_t count) & noexcept;
            row_iterator operator-(size_t count) const noexcept;
            row_iterator& operator--() & noexcept;
            row_iterator operator--(int) noexcept;

            std::ptrdiff_t operator-(const row_iterator& it)const noexcept;

            value_type operator*() noexcept;
        };

        class row_reverse_iterator final
        {
        private:

            matrix& _mat;
            size_t index;

        public:
            using difference_type = std::ptrdiff_t;
            using value_type = row_view;
            using pointer = row_view*;
            using reference = row_view&;
            using iterator_category = std::random_access_iterator_tag;

            row_reverse_iterator(matrix& mat, size_t ind = 0) noexcept;
            operator row_iterator() noexcept;

            row_reverse_iterator& operator+=(size_t count) & noexcept;
            row_reverse_iterator operator+(size_t count) const noexcept;
            row_reverse_iterator& operator++() & noexcept;
            row_reverse_iterator operator++(int) noexcept;

            row_reverse_iterator& operator-=(size_t count) & noexcept;
            row_reverse_iterator operator-(size_t count) const noexcept;
            row_reverse_iterator& operator--() & noexcept;
            row_reverse_iterator operator--(int) noexcept;

            std::ptrdiff_t operator-(const row_reverse_iterator& it)const noexcept;

            value_type operator*() noexcept;
        };

        class column_reverse_iterator;

        class column_iterator final
        {
        private:

            matrix& _mat;
            size_t index;

        public:
            using difference_type = std::ptrdiff_t;
            using value_type = column_view;
            using pointer = column_view*;
            using reference = column_view&;
            using iterator_category = std::random_access_iterator_tag;

            column_iterator(matrix& mat, size_t ind = 0) noexcept;
            operator column_reverse_iterator() noexcept;

            column_iterator& operator+=(size_t count) & noexcept;
            column_iterator operator+(size_t count) const noexcept;
            column_iterator& operator++() & noexcept;
            column_iterator operator++(int) noexcept;

            column_iterator& operator-=(size_t count) & noexcept;
            column_iterator operator-(size_t count) const noexcept;
            column_iterator& operator--() & noexcept;
            column_iterator operator--(int) noexcept;

            std::ptrdiff_t operator-(const column_iterator& it)const noexcept;

            value_type operator*() noexcept;
        };

        class column_reverse_iterator final
        {
        private:

            matrix& _mat;
            size_t index;

        public:
            using difference_type = std::ptrdiff_t;
            using value_type = column_view;
            using pointer = column_view*;
            using reference = column_view&;
            using iterator_category = std::random_access_iterator_tag;

            column_reverse_iterator(matrix& mat, size_t ind = 0) noexcept;
            operator column_iterator() noexcept;

            column_reverse_iterator& operator+=(size_t count) & noexcept;
            column_reverse_iterator operator+(size_t count) const noexcept;
            column_reverse_iterator& operator++() & noexcept;
            column_reverse_iterator operator++(int) noexcept;

            column_reverse_iterator& operator-=(size_t count) & noexcept;
            column_reverse_iterator operator-(size_t count) const noexcept;
            column_reverse_iterator& operator--() & noexcept;
            column_reverse_iterator operator--(int) noexcept;

            std::ptrdiff_t operator-(const column_reverse_iterator& it)const noexcept;

            value_type operator*() noexcept;
        };

        row_iterator begin();
        row_iterator end();
        row_reverse_iterator rbegin();
        row_reverse_iterator rend();

        row_iterator row_begin();
        row_iterator row_end();
        row_reverse_iterator row_rbegin();
        row_reverse_iterator row_rend();

        column_iterator column_begin();
        column_iterator column_end();
        column_reverse_iterator column_rbegin();
        column_reverse_iterator column_rend();
    };

    template<typename T>
    bool matrix<T>::row_view::equal_by_address(const matrix::row_view &other) const noexcept
    {
        return std::addressof(_mat) == std::addressof(other._mat) and _ind == other._ind;
    }

    template<typename T>
    bool matrix<T>::row_view::operator==(const matrix::row_view &other) const noexcept
    {
        if (size() != other.size())
            return false;

        for(auto && val: std::ranges::zip_view(*this, other))
        {
            if(std::get<0>(val) != std::get<1>(val))
                return false;
        }

        return true;
    }

    template<typename T>
    bool matrix<T>::row_view::operator==(const matrix::column_view &other) const noexcept
    {
        if (size() != other.size())
            return false;

        for(auto && val: std::ranges::zip_view(*this, other))
        {
            if(std::get<0>(val) != std::get<1>(val))
                return false;
        }

        return true;
    }

    template<typename T>
    size_t matrix<T>::row_view::size() const noexcept
    {
        return _mat.column_count();
    }

    template<typename T>
    T &matrix<T>::row_view::operator[](size_t ind)
    {
        return  _mat[ind, _ind];
    }

    template<typename T>
    matrix<T>::row_view &matrix<T>::row_view::operator=(const std::vector<T> &vec) &
    {
        for(auto && val: std::ranges::zip_view(*this, vec))
        {
            std::get<0>(val) = std::get<1>(val);
        }

        return *this;
    }

    template<typename T>
    matrix<T>::row_view &matrix<T>::row_view::operator=(std::vector<T> &&vec) &
    {
        for(auto && val: std::ranges::zip_view(*this, vec))
        {
            std::get<0>(val) = std::move(std::get<1>(val));
        }

        return *this;
    }

    template<typename T>
    matrix<T>::row_view &matrix<T>::row_view::operator=(const matrix::row_view &vec) &
    {
        for(auto && val: std::ranges::zip_view(*this, vec))
        {
            std::get<0>(val) = std::get<1>(val);
        }

        return *this;
    }

    template<typename T>
    matrix<T>::row_view &matrix<T>::row_view::operator=(matrix::row_view &&vec) &
    {
        for(auto && val: std::ranges::zip_view(*this, vec))
        {
            std::get<0>(val) = std::move(std::get<1>(val));
        }

        return *this;
    }

    template<typename T>
    matrix<T>::row_view &matrix<T>::row_view::operator=(const matrix::column_view &vec) &
    {
        for(auto && val: std::ranges::zip_view(*this, vec))
        {
            std::get<0>(val) = std::get<1>(val);
        }

        return *this;
    }

    template<typename T>
    matrix<T>::row_view &matrix<T>::row_view::operator=(matrix::column_view &&vec) &
    {
        for(auto && val: std::ranges::zip_view(*this, vec))
        {
            std::get<0>(val) = std::move(std::get<1>(val));
        }

        return *this;
    }

    template<typename T>
    matrix<T>::row_view &matrix<T>::row_view::operator+=(const matrix::row_view &other) &
    {
        for(auto && val: std::ranges::zip_view(*this, other))
        {
            std::get<0>(val) += std::get<1>(val);
        }

        return *this;
    }

    template<typename T>
    matrix<T>::row_view &matrix<T>::row_view::operator+=(const matrix::column_view &other) &
    {
        for(auto && val: std::ranges::zip_view(*this, other))
        {
            std::get<0>(val) += std::get<1>(val);
        }

        return *this;
    }

    template<typename T>
    matrix<T>::row_view &matrix<T>::row_view::operator-=(const matrix::row_view &other) &
    {
        for(auto && val: std::ranges::zip_view(*this, other))
        {
            std::get<0>(val) -= std::get<1>(val);
        }

        return *this;
    }

    template<typename T>
    matrix<T>::row_view &matrix<T>::row_view::operator-=(const matrix::column_view &other) &
    {
        for(auto && val: std::ranges::zip_view(*this, other))
        {
            std::get<0>(val) -= std::get<1>(val);
        }

        return *this;
    }

    template<typename T>
    T matrix<T>::row_view::operator*=(const matrix::row_view &other)
    {
        T res = 0;

        for(auto && val: std::ranges::zip_view(*this, other))
        {
            res += std::get<0>(val) * std::get<1>(val);
        }

        return res;
    }

    template<typename T>
    T matrix<T>::row_view::operator*=(const matrix::column_view &other)
    {
        T res = 0;

        for(auto && val: std::ranges::zip_view(*this, other))
        {
            res += std::get<0>(val) * std::get<1>(val);
        }

        return res;
    }

    template<typename T>
    matrix<T>::row_view &matrix<T>::row_view::operator*=(T other) &
    {
        for(auto && val: *this)
        {
            val *= other;
        }

        return *this;
    }

    template<typename T>
    matrix<T>::row_view &matrix<T>::row_view::operator/=(T other) &
    {
        for(auto && val: *this)
        {
            val /= other;
        }

        return *this;
    }

    template<typename T>
    void matrix<T>::row_view::swap(matrix::row_view other)
    {
        if (size() != other.size())
            throw std::logic_error("Swapping rows with different size");

        for(auto&& val : std::ranges::zip_view(*this, other))
        {
            std::swap(std::get<0>(val), std::get<1>(val));
        }
    }

    template<typename T>
    matrix<T>::row_view::row_view(matrix &mat, size_t ind) noexcept : _mat(mat), _ind(ind)
    {

    }

    template<typename T>
    matrix<T>::row_view::iterator matrix<T>::row_view::begin() noexcept
    {
        return {*this, 0};
    }

    template<typename T>
    matrix<T>::row_view::iterator matrix<T>::row_view::end() noexcept
    {
        return {*this, size()};
    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator matrix<T>::row_view::rbegin() noexcept
    {
        return {*this, 0};
    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator matrix<T>::row_view::rend() noexcept
    {
        return {*this, size()};
    }

    template<typename T>
    matrix<T>::row_view::iterator::iterator(const matrix::row_view &row, size_t ind) noexcept : _row(row), _ind(ind)
    {

    }

    template<typename T>
    matrix<T>::row_view::iterator::operator reverse_iterator() noexcept
    {
        return matrix::row_view::reverse_iterator(_row, _row.size() - _ind);
    }

    template<typename T>
    matrix<T>::row_view::iterator &matrix<T>::row_view::iterator::operator+=(size_t count) & noexcept
    {
        _ind += count;
        return *this;
    }

    template<typename T>
    matrix<T>::row_view::iterator matrix<T>::row_view::iterator::operator+(size_t count) const noexcept
    {
        auto cpy = *this;
        (*this) += count;
        return cpy;
    }

    template<typename T>
    matrix<T>::row_view::iterator &matrix<T>::row_view::iterator::operator++() & noexcept
    {
        ++_ind;
        return *this;
    }

    template<typename T>
    matrix<T>::row_view::iterator matrix<T>::row_view::iterator::operator++(int) noexcept
    {
        auto cpy = *this;
        ++(*this);
        return cpy;
    }

    template<typename T>
    matrix<T>::row_view::iterator &matrix<T>::row_view::iterator::operator-=(size_t count) & noexcept
    {
        _ind -= count;
        return *this;
    }

    template<typename T>
    matrix<T>::row_view::iterator matrix<T>::row_view::iterator::operator-(size_t count) const noexcept
    {
        auto cpy = *this;
        (*this) -= count;
        return cpy;
    }

    template<typename T>
    matrix<T>::row_view::iterator &matrix<T>::row_view::iterator::operator--() & noexcept
    {
        --_ind;
        return *this;
    }

    template<typename T>
    matrix<T>::row_view::iterator matrix<T>::row_view::iterator::operator--(int) noexcept
    {
        auto cpy = *this;
        --(*this);
        return cpy;
    }

    template<typename T>
    std::ptrdiff_t matrix<T>::row_view::iterator::operator-(const matrix::row_view::iterator &it) const noexcept
    {
        return (std::ptrdiff_t )_ind - (std::ptrdiff_t)it._ind;
    }

    template<typename T>
    matrix<T>::row_view::iterator::reference matrix<T>::row_view::iterator::operator*() noexcept
    {
        return _row[_ind];
    }

    template<typename T>
    matrix<T>::row_view::iterator::pointer matrix<T>::row_view::iterator::operator->() noexcept
    {
        return std::addressof(_row[_ind]);
    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator::operator iterator() noexcept
    {
        return matrix::row_view::iterator(_row, _row.size() - _ind);
    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator::reverse_iterator(const matrix::row_view &row, size_t ind) noexcept : _row(row), _ind(ind)
    {

    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator &matrix<T>::row_view::reverse_iterator::operator+=(size_t count) & noexcept
    {
        _ind += count;
        return *this;
    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator matrix<T>::row_view::reverse_iterator::operator+(size_t count) const noexcept
    {
        auto cpy = *this;
        (*this) += count;
        return cpy;
    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator &matrix<T>::row_view::reverse_iterator::operator++() & noexcept
    {
        ++_ind;
        return *this;
    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator matrix<T>::row_view::reverse_iterator::operator++(int) noexcept
    {
        auto cpy = *this;
        ++(*this);
        return cpy;
    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator &matrix<T>::row_view::reverse_iterator::operator-=(size_t count) & noexcept
    {
        _ind -= count;
        return *this;
    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator matrix<T>::row_view::reverse_iterator::operator-(size_t count) const noexcept
    {
        auto cpy = *this;
        (*this) -= count;
        return cpy;
    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator &matrix<T>::row_view::reverse_iterator::operator--() & noexcept
    {
        --_ind;
        return *this;
    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator matrix<T>::row_view::reverse_iterator::operator--(int) noexcept
    {
        auto cpy = *this;
        --(*this);
        return cpy;
    }

    template<typename T>
    std::ptrdiff_t
    matrix<T>::row_view::reverse_iterator::operator-(const matrix::row_view::reverse_iterator &it) const noexcept
    {
        return (std::ptrdiff_t )_ind - (std::ptrdiff_t )it._ind;
    }

    template<typename T>
    matrix<T>::row_view::reverse_iterator::reference matrix<T>::row_view::reverse_iterator::operator*() noexcept
    {
        return _row[_row.size() - _ind - 1];
    }

    template<typename T>
    typename matrix<T>::row_view::reverse_iterator::pointer matrix<T>::row_view::reverse_iterator::operator->() noexcept
    {
        return std::addressof(_row[_row.size() - _ind - 1]);
    }

    template<typename T>
    bool matrix<T>::column_view::equal_by_address(const matrix::column_view &other) const noexcept
    {
        return &_vec == &other._vec;
    }

    template<typename T>
    bool matrix<T>::column_view::operator==(const matrix::row_view &other) const noexcept
    {
        if (size() != other.size())
            return false;

        for(auto&& val : std::ranges::zip_view(*this, other))
        {
            if (std::get<0>(val) != std::get<1>(val))
            {
                return false;
            }
        }

        return true;
    }

    template<typename T>
    bool matrix<T>::column_view::operator==(const matrix::column_view &other) const noexcept
    {
        if (size() != other.size())
            return false;

        for(auto&& val : std::ranges::zip_view(*this, other))
        {
            if (std::get<0>(val) != std::get<1>(val))
            {
                return false;
            }
        }

        return true;
    }

    template<typename T>
    size_t matrix<T>::column_view::size() const noexcept
    {
        return _vec.size();
    }

    template<typename T>
    T &matrix<T>::column_view::operator[](size_t ind)
    {
        return _vec[ind];
    }

    template<typename T>
    matrix<T>::column_view &matrix<T>::column_view::operator=(const std::vector<T> &vec) &
    {
        if (size() != vec.size())
            throw std::logic_error("Called assign operation with vectors of different size");

        for(auto&& val : std::ranges::zip_view(*this, vec))
        {
            std::get<0>(val) += std::get<1>(val);
        }
    }

    template<typename T>
    matrix<T>::column_view &matrix<T>::column_view::operator=(std::vector<T> &&vec) &
    {
        if (size() != vec.size())
            throw std::logic_error("Called assign operation with vectors of different size");

        for(auto&& val : std::ranges::zip_view(*this, vec))
        {
            std::get<0>(val) += std::move(std::get<1>(val));
        }
    }

    template<typename T>
    matrix<T>::column_view &matrix<T>::column_view::operator=(const matrix::row_view &vec) &
    {
        if (size() != vec.size())
            throw std::logic_error("Called assign operation with vectors of different size");

        for(auto&& val : std::ranges::zip_view(*this, vec))
        {
            std::get<0>(val) += std::get<1>(val);
        }
    }

    template<typename T>
    matrix<T>::column_view &matrix<T>::column_view::operator=(matrix::row_view &&vec) &
    {
        if (size() != vec.size())
            throw std::logic_error("Called assign operation with vectors of different size");

        for(auto&& val : std::ranges::zip_view(*this, vec))
        {
            std::get<0>(val) += std::move(std::get<1>(val));
        }
    }

    template<typename T>
    matrix<T>::column_view &matrix<T>::column_view::operator=(const matrix::column_view &vec) &
    {
        if (size() != vec.size())
            throw std::logic_error("Called assign operation with vectors of different size");

        for(auto&& val : std::ranges::zip_view(*this, vec))
        {
            std::get<0>(val) += std::get<1>(val);
        }
    }

    template<typename T>
    matrix<T>::column_view &matrix<T>::column_view::operator=(matrix::column_view &&vec) &
    {
        if (size() != vec.size())
            throw std::logic_error("Called assign operation with vectors of different size");

        for(auto&& val : std::ranges::zip_view(*this, vec))
        {
            std::get<0>(val) += std::move(std::get<1>(val));
        }
    }

    template<typename T>
    matrix<T>::column_view &matrix<T>::column_view::operator+=(const matrix::row_view &other) &
    {
        if (size() != other.size())
            throw std::logic_error("Called plus operation with vectors of different size");

        for(auto&& val : std::ranges::zip_view(*this, other))
        {
            std::get<0>(val) += std::get<1>(val);
        }
    }

    template<typename T>
    matrix<T>::column_view &matrix<T>::column_view::operator+=(const matrix::column_view &other) &
    {
        if (size() != other.size())
            throw std::logic_error("Called plus operation with vectors of different size");

        for(auto&& val : std::ranges::zip_view(*this, other))
        {
            std::get<0>(val) += std::get<1>(val);
        }
    }

    template<typename T>
    matrix<T>::column_view &matrix<T>::column_view::operator-=(const matrix::row_view &other) &
    {
        if (size() != other.size())
            throw std::logic_error("Called minus operation with vectors of different size");

        for(auto&& val : std::ranges::zip_view(*this, other))
        {
            std::get<0>(val) -= std::get<1>(val);
        }
    }

    template<typename T>
    matrix<T>::column_view &matrix<T>::column_view::operator-=(const matrix::column_view &other) &
    {
        if (size() != other.size())
            throw std::logic_error("Called minus operation with vectors of different size");

        for(auto&& val : std::ranges::zip_view(*this, other))
        {
            std::get<0>(val) -= std::get<1>(val);
        }
    }

    template<typename T>
    T matrix<T>::column_view::operator*=(const matrix::row_view &other)
    {
        T val = 0;

        for (auto&& vals : std::ranges::zip_view(_vec, other))
        {
            val += std::get<0>(vals) * std::get<1>(vals);
        }

        return val;
    }

    template<typename T>
    T matrix<T>::column_view::operator*=(const matrix::column_view &other)
    {
        T val = 0;

        for (auto&& vals : std::ranges::zip_view(_vec, other))
        {
            val += std::get<0>(vals) * std::get<1>(vals);
        }

        return val;
    }

    template<typename T>
    matrix<T>::column_view &matrix<T>::column_view::operator*=(T other) &
    {
        for(auto&& val : *this)
        {
            val *= other;
        }

        return *this;
    }

    template<typename T>
    matrix<T>::column_view &matrix<T>::column_view::operator/=(T other) &
    {
        for(auto&& val : *this)
        {
            val /= other;
        }

        return *this;
    }

    template<typename T>
    void matrix<T>::column_view::swap(matrix::column_view other)
    {
        if (size() != other.size())
            throw std::logic_error("Swapping columns with different size");
        _vec.swap(other._vec);
    }

    template<typename T>
    matrix<T>::column_view::column_view(matrix::column_view::vector &vec) noexcept : _vec(vec)
    {

    }

    template<typename T>
    std::vector<T>::iterator matrix<T>::column_view::begin() noexcept
    {
        return _vec.begin();
    }

    template<typename T>
    std::vector<T>::iterator matrix<T>::column_view::end() noexcept
    {
        return _vec.end();
    }

    template<typename T>
    std::vector<T>::reverse_iterator matrix<T>::column_view::rbegin() noexcept
    {
        return _vec.rbegin();
    }

    template<typename T>
    std::vector<T>::reverse_iterator matrix<T>::column_view::rend() noexcept
    {
        return _vec.rend();
    }

    template<typename T>
    matrix<T> matrix<T>::identity(size_t size)
    {
        matrix res(size, size, 0);

        for(size_t i = 0; i < size; ++i)
        {
            res[i, i] = 1;
        }

        return res;
    }

    template<typename T>
    matrix<T> matrix<T>::as_matrix_row(const std::vector<size_t> &vec)
    {
        if (vec.size() == 0)
            return {};
        matrix res(vec.size(), 1, vec[0]);

        for(size_t i = 1; i < vec.size(); ++i)
        {
            res[0, i] = vec[i];
        }

        return res;
    }

    template<typename T>
    matrix<T> matrix<T>::as_matrix_row(std::vector<size_t> &&vec)
    {
        if (vec.size() == 0)
            return {};
        matrix res(vec.size(), 1, vec[0]);

        for(size_t i = 1; i < vec.size(); ++i)
        {
            res[0, i] = std::move(vec[i]);
        }

        return res;
    }

    template<typename T>
    matrix<T> matrix<T>::as_matrix_row(matrix::row_view vec)
    {
        if (vec.size() == 0)
            return {};
        matrix res(vec.size(), 1, vec[0]);

        for(size_t i = 1; i < vec.size(); ++i)
        {
            res[0, i] = vec[i];
        }

        return res;
    }

    template<typename T>
    matrix<T> matrix<T>::as_matrix_row(matrix::column_view vec)
    {
        if (vec.size() == 0)
            return {};
        matrix res(vec.size(), 1, vec[0]);

        for(size_t i = 1; i < vec.size(); ++i)
        {
            res[0, i] = vec[i];
        }

        return res;
    }

    template<typename T>
    matrix<T> matrix<T>::as_matrix_column(const std::vector<size_t> &vec)
    {
        if (vec.size() == 0)
            return {};
        matrix res(1, vec.size(), vec[0]);

        for(size_t i = 1; i < vec.size(); ++i)
        {
            res[i, 0] = vec[i];
        }

        return res;
    }

    template<typename T>
    matrix<T> matrix<T>::as_matrix_column(std::vector<size_t> &&vec)
    {
        if (vec.size() == 0)
            return {};
        matrix res(1, vec.size(), vec[0]);

        for(size_t i = 1; i < vec.size(); ++i)
        {
            res[i, 0] = std::move(vec[i]);
        }

        return res;
    }

    template<typename T>
    matrix<T> matrix<T>::as_matrix_column(matrix::row_view vec)
    {
        if (vec.size() == 0)
            return {};
        matrix res(1, vec.size(), vec[0]);

        for(size_t i = 1; i < vec.size(); ++i)
        {
            res[i, 0] = vec[i];
        }

        return res;
    }

    template<typename T>
    matrix<T> matrix<T>::as_matrix_column(matrix::column_view vec)
    {
        if (vec.size() == 0)
            return {};
        matrix res(1, vec.size(), vec[0]);

        for(size_t i = 1; i < vec.size(); ++i)
        {
            res[i, 0] = vec[i];
        }

        return res;
    }

    template<typename T>
    T &matrix<T>::operator[](size_t row, size_t column)
    {
        return data[column][row];
    }

    template<typename T>
    matrix<T>::row_view matrix<T>::operator[](size_t row)
    {
        return matrix::row_view(*this, row);
    }

    template<typename T>
    matrix<T>::row_view matrix<T>::get_row(size_t row)
    {
        return matrix::row_view(*this, row);
    }

    template<typename T>
    matrix<T>::column_view matrix<T>::get_column(size_t column)
    {
        return matrix::column_view(data[column]);
    }

    template<typename T>
    matrix<T>::matrix(size_t row_count, size_t column_count, const T &value)
    {
        data.reserve(column_count);

        for(size_t i = 0; i < column_count; ++i)
        {
            data.emplace_back(row_count, value);
        }
    }

    template<typename T>
    bool matrix<T>::operator==(const matrix &other) noexcept
    {
        if (column_count() != other.column_count() || row_count() != other.row_count())
            return false;

        for(auto&& columns : std::ranges::zip_view(data, other.data))
        {
            for(auto&& vals : std::ranges::zip_view(std::get<0>(columns), std::get<1>(columns)))
            {
                if(std::get<0>(vals) != std::get<1>(vals))
                    return false;
            }
        }

        return true;
    }


    template<typename T>
    matrix<T> &matrix<T>::operator+=(const matrix &other) &
    {
        if (row_count() != other.row_count() || column_count() != other.column_count())
        {
            throw std::logic_error("Attempt of minus operation with matrices with different dimensions");
        }

        for(auto&& columns : std::ranges::zip_view(data, other.data))
        {
            for(auto&& vals : std::ranges::zip_view(std::get<0>(columns), std::get<1>(columns)))
            {
                std::get<0>(vals) += std::get<1>(vals);
            }
        }

        return *this;
    }
    template<typename T>

    matrix<T> matrix<T>::operator+(const matrix &other)
    {
        auto cpy = *this;
        cpy += other;
        return cpy;
    }

    template<typename T>
    matrix<T> &matrix<T>::operator-=(const matrix &other) &
    {
        if (row_count() != other.row_count() || column_count() != other.column_count())
        {
            throw std::logic_error("Attempt of minus operation with matrices with different dimensions");
        }

        for(auto&& columns : std::ranges::zip_view(data, other.data))
        {
            for(auto&& vals : std::ranges::zip_view(std::get<0>(columns), std::get<1>(columns)))
            {
                std::get<0>(vals) -= std::get<1>(vals);
            }
        }

        return *this;
    }

    template<typename T>
    matrix<T> matrix<T>::operator-(const matrix &other)
    {
        auto cpy = *this;
        cpy -= other;
        return cpy;
    }

    template<typename T>
    matrix<T> &matrix<T>::operator*=(const T &other) &
    {
        for (auto&& col : data)
        {
            for(auto&& el : col)
            {
                el *= other;
            }
        }

        return *this;
    }

    template<typename T>
    matrix<T> matrix<T>::operator*(const T &other)
    {
        auto cpy = *this;
        cpy *= other;
        return cpy;
    }

    template<typename T>
    matrix<T> &matrix<T>::operator/=(const T &other) &
    {
        for (auto&& col : data)
        {
            for(auto&& el : col)
            {
                el /= other;
            }
        }

        return *this;
    }

    template<typename T>
    matrix<T> matrix<T>::operator/(const T &other)
    {
        auto cpy = *this;
        cpy /= other;
        return cpy;
    }

    template<typename T>
    size_t matrix<T>::row_count() const noexcept
    {
        return data.empty() ? 0 : data[0].size();
    }

    template<typename T>
    size_t matrix<T>::column_count() const noexcept
    {
        return data.size();
    }

    template<typename T>
    void matrix<T>::set_row_count(size_t c, const T &val)
    {
        if (c < row_count())
        {
            for (auto&& vec : data)
            {
                vec.resize(c);
            }
        } else if (c > row_count())
        {
            for (auto&& vec : data)
            {
                vec.resize(c, val);
            }
        }
    }

    template<typename T>
    void matrix<T>::set_column_count(size_t c, const T &val)
    {
        if (c < column_count())
        {
            data.resize(c);
        } else if (c > column_count())
        {
            std::vector<T> vec(row_count(), val);
            data.resize(c, vec);
        }
    }

    template<typename T>
    void matrix<T>::swap_rows(size_t f, size_t r)
    {
        get_row(f).swap(get_row(r));
    }

    template<typename T>
    void matrix<T>::swap_columns(size_t f, size_t r)
    {
        get_column(f).swap(get_column(r));
    }

    template<typename T>
    matrix<T> matrix<T>::minor(size_t r, size_t c)
    {
        if(column_count() == 0 || row_count() == 0)
        {
            throw std::logic_error("Attempt of getting minor of empty matrix");
        }

        if (r >= row_count() || c >= column_count())
        {
            throw std::logic_error("Coordinates are out of bounds while getting minor");
        }

        matrix res(row_count() - 1, column_count() - 1, (*this)[0, 0]);

        for (size_t i = 0; i < row_count() - 1; ++i)
        {
            for (size_t j = 0; j < column_count() - 1; ++j)
            {
                res[i, j] = (*this)[i < r ? i : i + 1, j < c ? j : j + 1];
            }
        }

        return res;
    }

    template<typename T>
    matrix<T> &matrix<T>::transpose() &
    {
        *this = transposed();
        return *this;
    }

    template<typename T>
    matrix<T> matrix<T>::transposed()
    {
        if (column_count() == 0 || row_count() == 0)
            return *this;

        matrix res(column_count(), row_count(), (*this)[0, 0]);

        for(size_t i = 0; i < row_count(); ++i)
        {
            for(size_t j = 0; j < column_count(); ++j)
            {
                res[j, i] = (*this)[i, j];
            }
        }

        return res;
    }


    template<typename T>
    matrix<T>::row_iterator::row_iterator(matrix &mat, size_t ind) noexcept : _mat(mat), index(ind)
    {

    }

    template<typename T>
    matrix<T>::row_iterator::operator row_reverse_iterator() noexcept {
        return row_reverse_iterator(_mat, _mat.row_count() - index);
    }

    template<typename T>
    typename matrix<T>::row_iterator &matrix<T>::row_iterator::operator+=(size_t count) & noexcept
    {
        index += count;
        return *this;
    }

    template<typename T>
    typename matrix<T>::row_iterator matrix<T>::row_iterator::operator+(size_t count) const noexcept
    {
        auto cpy = *this;
        cpy += count;
        return cpy;
    }

    template<typename T>
    typename matrix<T>::row_iterator &matrix<T>::row_iterator::operator++() & noexcept
    {
        ++index;
        return *this;
    }

    template<typename T>
    typename matrix<T>::row_iterator matrix<T>::row_iterator::operator++(int)  noexcept
    {
        auto cpy = *this;
        ++(*this);
        return cpy;
    }

    template<typename T>
    typename matrix<T>::row_iterator &matrix<T>::row_iterator::operator-=(size_t count) & noexcept
    {
        index -= count;
        return *this;
    }

    template<typename T>
    typename matrix<T>::row_iterator matrix<T>::row_iterator::operator-(size_t count) const noexcept
    {
        auto cpy = *this;
        cpy -= count;
        return cpy;
    }

    template<typename T>
    typename matrix<T>::row_iterator &matrix<T>::row_iterator::operator--() & noexcept
    {
        --index;
        return *this;
    }

    template<typename T>
    typename matrix<T>::row_iterator matrix<T>::row_iterator::operator--(int) noexcept
    {
        auto cpy = *this;
        --(*this);
        return cpy;
    }

    template<typename T>
    std::ptrdiff_t matrix<T>::row_iterator::operator-(const matrix::row_iterator &it) const noexcept
    {
        return static_cast<std::ptrdiff_t>(index) - static_cast<std::ptrdiff_t>(it.index);
    }

    template<typename T>
    typename matrix<T>::row_iterator::value_type matrix<T>::row_iterator::operator*() noexcept
    {
        return _mat.get_row(index);
    }

    template<typename T>
    matrix<T>::row_reverse_iterator::row_reverse_iterator(matrix &mat, size_t ind) noexcept : _mat(mat), index(ind)
    {

    }

    template<typename T>
    matrix<T>::row_reverse_iterator::operator row_iterator() noexcept {
        return row_iterator(_mat, _mat.row_count() - index);
    }

    template<typename T>
    typename matrix<T>::row_reverse_iterator &matrix<T>::row_reverse_iterator::operator+=(size_t count) & noexcept
    {
        index += count;
        return *this;
    }

    template<typename T>
    typename matrix<T>::row_reverse_iterator matrix<T>::row_reverse_iterator::operator+(size_t count) const noexcept
    {
        auto cpy = *this;
        cpy += count;
        return cpy;
    }

    template<typename T>
    typename matrix<T>::row_reverse_iterator &matrix<T>::row_reverse_iterator::operator++() & noexcept
    {
        ++index;
        return *this;
    }

    template<typename T>
    typename matrix<T>::row_reverse_iterator matrix<T>::row_reverse_iterator::operator++(int)  noexcept
    {
        auto cpy = *this;
        ++(*this);
        return cpy;
    }

    template<typename T>
    typename matrix<T>::row_reverse_iterator &matrix<T>::row_reverse_iterator::operator-=(size_t count) & noexcept
    {
        index -= count;
        return *this;
    }

    template<typename T>
    typename matrix<T>::row_reverse_iterator matrix<T>::row_reverse_iterator::operator-(size_t count) const noexcept
    {
        auto cpy = *this;
        cpy -= count;
        return cpy;
    }

    template<typename T>
    typename matrix<T>::row_reverse_iterator &matrix<T>::row_reverse_iterator::operator--() & noexcept
    {
        --index;
        return *this;
    }

    template<typename T>
    typename matrix<T>::row_reverse_iterator matrix<T>::row_reverse_iterator::operator--(int) noexcept
    {
        auto cpy = *this;
        --(*this);
        return cpy;
    }

    template<typename T>
    std::ptrdiff_t matrix<T>::row_reverse_iterator::operator-(const matrix::row_reverse_iterator &it) const noexcept
    {
        return static_cast<std::ptrdiff_t>(index) - static_cast<std::ptrdiff_t>(it.index);
    }

    template<typename T>
    typename matrix<T>::row_reverse_iterator::value_type matrix<T>::row_reverse_iterator::operator*() noexcept
    {
        return _mat.get_row(_mat.row_count() - index - 1);
    }

    template<typename T>
    matrix<T>::column_iterator::column_iterator(matrix &mat, size_t ind) noexcept : _mat(mat), index(ind)
    {

    }

    template<typename T>
    matrix<T>::column_iterator::operator column_reverse_iterator() noexcept {
        return column_reverse_iterator(_mat, _mat.column_count() - index);
    }

    template<typename T>
    typename matrix<T>::column_iterator &matrix<T>::column_iterator::operator+=(size_t count) & noexcept
    {
        index += count;
        return *this;
    }

    template<typename T>
    typename matrix<T>::column_iterator matrix<T>::column_iterator::operator+(size_t count) const noexcept
    {
        auto cpy = *this;
        cpy += count;
        return cpy;
    }

    template<typename T>
    typename matrix<T>::column_iterator &matrix<T>::column_iterator::operator++() & noexcept
    {
        ++index;
        return *this;
    }

    template<typename T>
    typename matrix<T>::column_iterator matrix<T>::column_iterator::operator++(int)  noexcept
    {
        auto cpy = *this;
        ++(*this);
        return cpy;
    }

    template<typename T>
    typename matrix<T>::column_iterator &matrix<T>::column_iterator::operator-=(size_t count) & noexcept
    {
        index -= count;
        return *this;
    }

    template<typename T>
    typename matrix<T>::column_iterator matrix<T>::column_iterator::operator-(size_t count) const noexcept
    {
        auto cpy = *this;
        cpy -= count;
        return cpy;
    }

    template<typename T>
    typename matrix<T>::column_iterator &matrix<T>::column_iterator::operator--() & noexcept
    {
        --index;
        return *this;
    }

    template<typename T>
    typename matrix<T>::column_iterator matrix<T>::column_iterator::operator--(int) noexcept
    {
        auto cpy = *this;
        --(*this);
        return cpy;
    }

    template<typename T>
    std::ptrdiff_t matrix<T>::column_iterator::operator-(const matrix::column_iterator &it) const noexcept
    {
        return static_cast<std::ptrdiff_t>(index) - static_cast<std::ptrdiff_t>(it.index);
    }

    template<typename T>
    typename matrix<T>::column_iterator::value_type matrix<T>::column_iterator::operator*() noexcept
    {
        return _mat.get_column(index);
    }

	template<typename T>
	matrix<T>::column_reverse_iterator::column_reverse_iterator(matrix &mat, size_t ind) noexcept : _mat(mat), index(ind)
	{

	}

	template<typename T>
	matrix<T>::column_reverse_iterator::operator column_iterator() noexcept {
		return column_iterator(_mat, _mat.column_count() - index);
	}

	template<typename T>
	typename matrix<T>::column_reverse_iterator &matrix<T>::column_reverse_iterator::operator+=(size_t count) & noexcept
	{
		index += count;
		return *this;
	}

	template<typename T>
	typename matrix<T>::column_reverse_iterator matrix<T>::column_reverse_iterator::operator+(size_t count) const noexcept
	{
		auto cpy = *this;
		cpy += count;
		return cpy;
	}

	template<typename T>
	typename matrix<T>::column_reverse_iterator &matrix<T>::column_reverse_iterator::operator++() & noexcept
	{
		++index;
		return *this;
	}

	template<typename T>
	typename matrix<T>::column_reverse_iterator matrix<T>::column_reverse_iterator::operator++(int)  noexcept
	{
		auto cpy = *this;
		++(*this);
		return cpy;
	}

	template<typename T>
	typename matrix<T>::column_reverse_iterator &matrix<T>::column_reverse_iterator::operator-=(size_t count) & noexcept
	{
		index -= count;
		return *this;
	}

	template<typename T>
	typename matrix<T>::column_reverse_iterator matrix<T>::column_reverse_iterator::operator-(size_t count) const noexcept
	{
		auto cpy = *this;
		cpy -= count;
		return cpy;
	}

	template<typename T>
	typename matrix<T>::column_reverse_iterator &matrix<T>::column_reverse_iterator::operator--() & noexcept
	{
		--index;
		return *this;
	}

	template<typename T>
	typename matrix<T>::column_reverse_iterator matrix<T>::column_reverse_iterator::operator--(int) noexcept
	{
		auto cpy = *this;
		--(*this);
		return cpy;
	}

	template<typename T>
	std::ptrdiff_t matrix<T>::column_reverse_iterator::operator-(const matrix::column_reverse_iterator &it) const noexcept
	{
		return static_cast<std::ptrdiff_t>(index) - static_cast<std::ptrdiff_t>(it.index);
	}

	template<typename T>
	typename matrix<T>::column_reverse_iterator::value_type matrix<T>::column_reverse_iterator::operator*() noexcept
	{
		return _mat.get_column(_mat.column_count() - index - 1);
	}

	template<typename T>
	typename matrix<T>::row_iterator matrix<T>::begin()
	{
		return matrix::row_iterator(*this, 0);
	}

	template<typename T>
	typename matrix<T>::row_iterator matrix<T>::end()
	{
		return matrix::row_iterator(*this, row_count());
	}

	template<typename T>
	typename matrix<T>::row_reverse_iterator matrix<T>::rbegin()
	{
		return matrix::row_reverse_iterator(*this, 0);
	}

	template<typename T>
	typename matrix<T>::row_reverse_iterator matrix<T>::rend()
	{
		return matrix::row_reverse_iterator(*this, row_count());
	}

	template<typename T>
	typename matrix<T>::row_iterator matrix<T>::row_begin()
	{
		return matrix::row_iterator(*this, 0);
	}

	template<typename T>
	typename matrix<T>::row_iterator matrix<T>::row_end()
	{
		return matrix::row_iterator(*this, row_count());
	}

	template<typename T>
	typename matrix<T>::row_reverse_iterator matrix<T>::row_rbegin()
	{
		return matrix::row_reverse_iterator(*this, 0);
	}

	template<typename T>
	typename matrix<T>::row_reverse_iterator matrix<T>::row_rend()
	{
		return matrix::row_reverse_iterator(*this, row_count());
	}

	template<typename T>
	typename matrix<T>::column_iterator matrix<T>::column_begin()
	{
		return matrix::column_iterator(*this, 0);
	}

	template<typename T>
	typename matrix<T>::column_iterator matrix<T>::column_end()
	{
		return matrix::column_iterator(*this, column_count());
	}

	template<typename T>
	typename matrix<T>::column_reverse_iterator matrix<T>::column_rbegin()
	{
		return matrix::column_reverse_iterator(*this, 0);
	}

	template<typename T>
	typename matrix<T>::column_reverse_iterator matrix<T>::column_rend()
	{
		return matrix::column_reverse_iterator(*this, column_count());
	}
}

#endif //NUMEROLOGY_MATRIX_HPP
