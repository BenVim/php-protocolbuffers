// Copyright 2013 Shuhei Tanuma.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef GOOGLE_PROTOBUF_COMPILER_PHP_ENUM_H__
#define GOOGLE_PROTOBUF_COMPILER_PHP_ENUM_H__

#include <string>
#include <vector>
#include <google/protobuf/descriptor.h>

namespace google {
namespace protobuf {
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace php {

class EnumGenerator {
    public:
    EnumGenerator(const EnumDescriptor* descriptor, GeneratorContext* context);
    ~EnumGenerator();

    void Generate(io::Printer* printer);
    string FileName();
    void PrintUseNameSpaceIfNeeded(io::Printer* printer);
    string NameSpace();

    private:
        string ClassName();

        bool use_namespace_;
        bool enclose_namespace_;
        const EnumDescriptor *descriptor_;
        GeneratorContext* context_;
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_PHP_ENUM_H__
