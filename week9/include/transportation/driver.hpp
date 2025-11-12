#pragma once

#include <string>

namespace transportation
{
    // Represents a driver for a (non-autonomous) Taxi.
    class Driver
    {
    public:
        // Constructor
        Driver(const std::string &id, const std::string &name, const std::string &license_num)
            : id_{id}, name_{name}, license_number_{license_num} {}

        // Getters
        [[nodiscard]] std::string get_id() const noexcept { return id_; }
        [[nodiscard]] std::string get_name() const noexcept { return name_; }
        [[nodiscard]] std::string get_license_number() const noexcept { return license_number_; }
        [[nodiscard]] float get_rating() const noexcept { return rating_; }

        // Setters
        void set_id(const std::string &id) { id_ = id; }
        void set_name(const std::string &name) { name_ = name; }
        void set_license_number(const std::string &license_num) { license_number_ = license_num; }
        void set_rating(float rating) { rating_ = rating; }

        // No other methods specified in diagram

    private:
        std::string id_;
        std::string name_;
        std::string license_number_;
        float rating_{5.0f};
    };
} // namespace transportation