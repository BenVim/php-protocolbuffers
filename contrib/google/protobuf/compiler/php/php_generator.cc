// Copyright 2013 Shuhei Tanuma.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "./php_generator.h"
#include "./php_helpers.h"

#include <utility>

namespace google {
namespace protobuf {
namespace compiler {
namespace php {

PHPGenerator::PHPGenerator() {
}

PHPGenerator::~PHPGenerator() {
}

bool PHPGenerator::Generate(const FileDescriptor* file,
                         const string& parameter,
                         GeneratorContext* context,
                         string* error) const {
    bool result = true;
    string output_list_file;
    vector<string> all_files;
    vector<pair<string, string> > options;
    ParseGeneratorParameter(parameter, &options);

    for (int i = 0; i < options.size(); i++) {
        if (options[i].first == "output_list_file") {
            output_list_file = options[i].second;
        } else {
            *error = "Unknown generator option: " + options[i].first;
            return false;
        }
    }

    FileGenerator file_generator(file, context);
    if (!file_generator.Validate(error)) {
        return false;
    }

    string package_name = PhpPackageToDir(file_generator.php_package());

    // TODO(chobie): Generate php main file.
    scoped_ptr<io::ZeroCopyOutputStream> output(
        context->Open("autoload.php"));
    io::Printer printer(output.get(), '`');
    file_generator.Generate(&printer);

    file_generator.GenerateSiblings(package_name, context, &all_files);
    if (!output_list_file.empty()) {
        // TODO(chobie): Outputs file
    }

    return result;
}

}  // namespace php
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
