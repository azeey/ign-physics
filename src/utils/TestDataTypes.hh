/*
 * Copyright (C) 2017 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef IGNITION_PHYSICS_TESTUTILS_HH_
#define IGNITION_PHYSICS_TESTUTILS_HH_

#include "ignition/physics/CompositeData.hh"
#include "ignition/physics/CompositeDataMacros.hh"
#include "ignition/physics/SpecifyData.hh"

/////////////////////////////////////////////////
class StringData
{
  IGN_PHYSICS_DATA_LABEL(StringData)
  public: std::string myString;

  public: inline StringData(const std::string &_input = "default")
    : myString(_input)
  {
    // Do nothing
  }
};

/////////////////////////////////////////////////
class DoubleData
{
  IGN_PHYSICS_DATA_LABEL(DoubleData)
  public: double myDouble;

  public: inline DoubleData(const double _input = 1.61803)
    : myDouble(_input)
  {
    // Do nothing
  }
};

/////////////////////////////////////////////////
class IntData
{
  IGN_PHYSICS_DATA_LABEL(IntData)
  public: int myInt;

  public: inline IntData(const int _input = 55)
    : myInt(_input)
  {
    // Do nothing
  }
};

/////////////////////////////////////////////////
class BoolData
{
  IGN_PHYSICS_DATA_LABEL(BoolData)
  public: bool myBool;

  public: inline BoolData(const bool _input = true)
    : myBool(_input)
  {
    // Do nothing
  }
};

/////////////////////////////////////////////////
class CharData
{
  IGN_PHYSICS_DATA_LABEL(CharData)
  public: char myChar;

  public: inline CharData(const char _input = 'c')
    : myChar(_input)
  {
    // Do nothing
  }
};

/////////////////////////////////////////////////
class FloatData
{
  IGN_PHYSICS_DATA_LABEL(FloatData)
  public: float myFloat;

  public: inline FloatData(const float _input = 9.5)
    : myFloat(_input)
  {
    // Do nothing
  }
};

/////////////////////////////////////////////////
class VectorDoubleData
{
  IGN_PHYSICS_DATA_LABEL(VectorDoubleData)
  public: std::vector<double> myVector;

  public: inline VectorDoubleData(const std::vector<double> &vec = {})
    : myVector(vec)
  {
    // Do nothing
  }
};

/////////////////////////////////////////////////
// Single-requirement CompositeData
using RequireString = ignition::physics::RequireData<StringData>;

// CompositeData with three requirements and two optional expectations
using RequireStringBoolChar = ignition::physics::SpecifyData<
          ignition::physics::RequireData<
                StringData,
                BoolData,
                CharData>,
          ignition::physics::ExpectData<
                IntData,
                FloatData> >;

// CompositeData with two requirements and two optional expectations
using RequireIntDouble = ignition::physics::SpecifyData<
          ignition::physics::RequireData<
                DoubleData,
                IntData>,
          ignition::physics::ExpectData<
                StringData,
                CharData> >;

/////////////////////////////////////////////////
template <typename... DataTypes>
struct AddSomeData
{
  // This class definition is just here for syntax reasons
};

template <typename DataType>
struct AddSomeData<DataType>
{
  static void To(ignition::physics::CompositeData &data)
  {
    data.Create<DataType>();
  }
};

template <typename DataType1, typename... OtherDataTypes>
struct AddSomeData<DataType1, OtherDataTypes...>
{
  static void To(ignition::physics::CompositeData &data)
  {
    data.Create<DataType1>();
    AddSomeData<OtherDataTypes...>::To(data);
  }
};

/////////////////////////////////////////////////
template <typename... DataTypes>
ignition::physics::CompositeData CreateSomeData(bool resetQueries = false)
{
  ignition::physics::CompositeData data;
  AddSomeData<DataTypes...>::To(data);

  if(resetQueries)
    data.ResetQueries();

  return data;
}


#endif