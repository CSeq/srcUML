/**
 * @file srcyuml_attribute.hpp
 *
 * @copyright Copyright (C) 2016 srcML, LLC. (www.srcML.org)
 *
 * This file is part of srcYUML.
 *
 * srcYUML is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * srcYUML is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with srcYUML.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INCLUDED_SRCYUML_ATTRIBUTE_HPP
#define INCLUDED_SRCYUML_ATTRIBUTE_HPP

#include <DeclTypePolicySingleEvent.hpp>

#include <srcyuml_type.hpp>
#include <string>

class srcyuml_attribute {

private:

    const DeclTypePolicy::DeclTypeData * data;
    const ClassPolicy::AccessSpecifier visibility;

    srcyuml_type type;
    std::string name;

    bool is_pointer;
    bool has_index;
    std::string index;

public:
    srcyuml_attribute(const DeclTypePolicy::DeclTypeData * data, ClassPolicy::AccessSpecifier visibility)
        : data(data),
          visibility(visibility),
          type(data->type),
          name(data->name ? data->name->ToString() : ""),
          is_pointer(type.get_is_pointer()),
          has_index(false),
          index() {

            analyze_attribute();

    }

    const srcyuml_type & get_type() const {
        return type;
    }

    // ~srcyuml_attribute() { if(data) delete data; }

    friend std::ostream & operator<<(std::ostream & out, const srcyuml_attribute & attribute) {

        if(attribute.visibility == ClassPolicy::PUBLIC)
            out << '+';
        else if(attribute.visibility == ClassPolicy::PRIVATE)
            out << '-';
        else if(attribute.visibility == ClassPolicy::PROTECTED)
            out << '#';

        out << " " << attribute.name << ": " << attribute.type;

        if(!attribute.index.empty()) {

            out << "［";
            if(attribute.is_pointer)
                out << "0..";
            out << attribute.index;
            out << "］";

        } else if(attribute.is_pointer
            || attribute.has_index
            || attribute.type.get_is_container()) {
            out << "［*］";
        } else if(attribute.type.get_is_smart_pointer()) {
            out << "［0..1］";
        }

        out << ';';

        return out;

    }

private:
    void analyze_attribute() {

        if(!data->name) return;

        if(!data->name->arrayIndices.empty()) {
            has_index = true;
            index = data->name->arrayIndices[0];
        } else if(type.get_has_index()) {
            has_index = true;
            index = type.get_index();
        }

    }

};

 #endif