#include "protoc-gen-php.h"

/**
 * Copyright (c) 2012, Andrew Brampton
 * Copyright (c) 2013, Shuhei Tanuma
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

namespace google {
namespace protobuf {
namespace compiler {
namespace php {

string UnderscoresToCamelCaseImpl(const string& input, bool cap_next_letter) {
    string result;
    // Note:  I distrust ctype.h due to locales.
    for (int i = 0; i < (int)input.size(); i++) {
        if ('a' <= input[i] && input[i] <= 'z') {
            if (cap_next_letter) {
                result += input[i] + ('A' - 'a');
            } else {
                result += input[i];
            }
            cap_next_letter = false;
        } else if ('A' <= input[i] && input[i] <= 'Z') {
            if (i == 0 && !cap_next_letter) {
                // Force first letter to lower-case unless explicitly told to
                // capitalize it.
                result += input[i] + ('a' - 'A');
            } else {
                // Capital letters after the first are left as-is.
                result += input[i];
            }
            cap_next_letter = false;
        } else if ('0' <= input[i] && input[i] <= '9') {
            result += input[i];
            cap_next_letter = true;
        } else {
            cap_next_letter = true;
        }
    }
    return result;
}

string UnderscoresToCamelCase(const FieldDescriptor& field) {
    return UnderscoresToCamelCaseImpl(field.name(), false);
}

string UnderscoresToCapitalizedCamelCase(const FieldDescriptor& field) {
    return UnderscoresToCamelCaseImpl(field.name(), true);
}

string LowerString(const string & s) {
    string newS(s);

    google::protobuf::LowerString(&newS);
    return newS;
}

string UpperString(const string & s) {
    string newS (s);

    google::protobuf::UpperString(&newS);
    return newS;
}


PHPCodeGenerator::PHPCodeGenerator() {}
PHPCodeGenerator::~PHPCodeGenerator() {}


// Maps a Message full_name into a PHP name
template <class DescriptorType>
    string PHPCodeGenerator::ClassName(const DescriptorType & descriptor) const {
        string name (descriptor.full_name());

        replace(name.begin(), name.end(), '.', '_');

        return name;
    }

string PHPCodeGenerator::VariableName(const FieldDescriptor & field) const {
    return field.name();
}

string PHPCodeGenerator::DefaultValueAsString(const FieldDescriptor & field, bool quote_string_type) const {
    switch (field.cpp_type()) {
        case FieldDescriptor::CPPTYPE_INT32:
            return SimpleItoa(field.default_value_int32());

        case FieldDescriptor::CPPTYPE_INT64:
            return SimpleItoa(field.default_value_int64());

        case FieldDescriptor::CPPTYPE_UINT32:
            return SimpleItoa(field.default_value_uint32());

        case FieldDescriptor::CPPTYPE_UINT64:
            return SimpleItoa(field.default_value_uint64());

        case FieldDescriptor::CPPTYPE_FLOAT:
            return SimpleFtoa(field.default_value_float());

        case FieldDescriptor::CPPTYPE_DOUBLE:
            return SimpleDtoa(field.default_value_double());

        case FieldDescriptor::CPPTYPE_BOOL:
            return (field.default_value_bool()) ? "true" : "false";
        case FieldDescriptor::CPPTYPE_STRING:
            if (quote_string_type)
                return "\"" + CEscape(field.default_value_string()) + "\"";

            if (field.type() == FieldDescriptor::TYPE_BYTES)
                return CEscape(field.default_value_string());

            return field.default_value_string();

        case FieldDescriptor::CPPTYPE_ENUM:
            return ClassName(*field.enum_type()) + "::" + field.default_value_enum()->name();

        case FieldDescriptor::CPPTYPE_MESSAGE:
            return "null";

    }
    return "";
}

string getTypeName(const FieldDescriptor & field){

    if (field.is_repeated()) {
        return "array";
    }

    switch (field.type()) {
        case FieldDescriptorProto_Type_TYPE_DOUBLE:
            return "double";
            break;
        case FieldDescriptorProto_Type_TYPE_FLOAT:
            return "float";
            break;
        case FieldDescriptorProto_Type_TYPE_INT64:
            return "int";
            break;
        case FieldDescriptorProto_Type_TYPE_UINT64:
            return "int";
            break;
        case FieldDescriptorProto_Type_TYPE_INT32:
            return "int";
            break;
        case FieldDescriptorProto_Type_TYPE_FIXED64:
            return "int";
            break;
        case FieldDescriptorProto_Type_TYPE_FIXED32:
            return "int";
            break;
        case FieldDescriptorProto_Type_TYPE_BOOL:
            return "bool";
            break;
        case FieldDescriptorProto_Type_TYPE_STRING:
            return "string";
            break;
        case FieldDescriptorProto_Type_TYPE_GROUP:
            return "";
            break;
        case FieldDescriptorProto_Type_TYPE_MESSAGE:
            {
                string name = (*field.message_type()).full_name();
                replace(name.begin(), name.end(), '.', '_');

                return name;

            }
            break;
        case FieldDescriptorProto_Type_TYPE_BYTES:
            return "string";
            break;
        case FieldDescriptorProto_Type_TYPE_UINT32:
            return "int";
            break;
        case FieldDescriptorProto_Type_TYPE_ENUM:
            return "int";
            break;
        case FieldDescriptorProto_Type_TYPE_SFIXED32:
            return "int";
            break;
        case FieldDescriptorProto_Type_TYPE_SFIXED64:
            return "int";
            break;
        case FieldDescriptorProto_Type_TYPE_SINT32:
            return "int";
            break;
        case FieldDescriptorProto_Type_TYPE_SINT64:
            return "int";
            break;
    }
    return "";
}

static const char *fields_map[] = {
    "DUMMY",
    "ProtocolBuffers::TYPE_DOUBLE",
    "ProtocolBuffers::TYPE_FLOAT",
    "ProtocolBuffers::TYPE_INT64",
    "ProtocolBuffers::TYPE_UINT64",
    "ProtocolBuffers::TYPE_INT32",
    "ProtocolBuffers::TYPE_FIXED64",
    "ProtocolBuffers::TYPE_FIXED32",
    "ProtocolBuffers::TYPE_BOOL",
    "ProtocolBuffers::TYPE_STRING",
    "ProtocolBuffers::TYPE_GROUP",
    "ProtocolBuffers::TYPE_MESSAGE",
    "ProtocolBuffers::TYPE_BYTES",
    "ProtocolBuffers::TYPE_UINT32",
    "ProtocolBuffers::TYPE_ENUM",
    "ProtocolBuffers::TYPE_SFIXED32",
    "ProtocolBuffers::TYPE_SFIXED64",
    "ProtocolBuffers::TYPE_SINT32",
    "ProtocolBuffers::TYPE_SINT64",
};

static const char* field_type_to_str(int field_type)
{
    if (field_type > 0 && field_type <= 18) {
        return fields_map[field_type];
    } else {
        return NULL;
    }
}

void PHPCodeGenerator::PrintMessageRead(io::Printer &printer, const Descriptor & message, vector<const FieldDescriptor *> & required_fields, const FieldDescriptor * parentField) const {
}

/**
 * Turns a 32 bit number into a string suitable for PHP to print out.
 * For example, 0x12345678 would turn into "\x12\x34\x56\78".
 * @param tag
 * @return
 */
string arrayToPHPString(uint8 *a, size_t len) {

    assert(a != NULL);

    const int dest_length = len * 4 + 1; // Maximum possible expansion
    scoped_array<char> dest(new char[dest_length]);

    char *p = dest.get();

    while(len > 0) {
        uint8 c = *a++;
        if ((c >= 0 && c <= 31) || c >= 127 ) {
            p += sprintf(p, "\\x%02x", c);
        } else if (c == '"'){
            *p++ = '\\';
            *p++ = c;
        } else {
            *p++ = c;
        }

        len--;
    }

    *p = '\0'; // Null terminate us

    return string(dest.get());
}

/**
 * Some notes
 * Tag    <varint fieldID wireType>
 * Field  <tag> <value>
 * Length <tag> <len> <data>
 * Group  <start tag> <field>+ <end tag>
 * Embedded Message <tag> <len> <field>+
 * Start <field>+ (You have to know what type of Message it is, and it is not length prefixed)
 *
 * The Message class should not print its own length (this should be printed by the parent Message)
 * The Group class should only print its field, the parent should print the start/end tag
 * Otherwise the Message/Group will print everything of the fields.
 */

/**
 * Prints the write() method for this Message
 * @param printer
 * @param message
 * @param parentField
 */
void PHPCodeGenerator::PrintMessageWrite(io::Printer &printer, const Descriptor & message, const FieldDescriptor * parentField) const {
}

void PHPCodeGenerator::PrintMessageSize(io::Printer &printer, const Descriptor & message) const {
    //	const PHPFileOptions& options(message.file()->options().GetExtension(php));
    //	const char * pb_namespace = options.namespace_().empty() ? "" : "\\";

}

void PHPCodeGenerator::PrintMessage(io::Printer &printer, const Descriptor &message) const {
    // Parse the file options

    const PHPFileOptions& options = message.file()->options().GetExtension(::php);
    bool  skip_unknown        = options.skip_unknown();
    const char * pb_namespace = options.namespace_().empty() ? "" : "\\";
    const PHPMessageOptions& moptions = message.options().GetExtension(::php_option);

    vector<const FieldDescriptor *> required_fields;

    // Print nested messages
    for (int i = 0; i < message.nested_type_count(); ++i) {
        printer.Print("\n");
        PrintMessage(printer, *message.nested_type(i));
    }

    // Print nested enum
    for (int i = 0; i < message.enum_type_count(); ++i) {
        PrintEnum(printer, *message.enum_type(i) );
    }

    // Find out if we are a nested type, if so what kind
    const FieldDescriptor * parentField = NULL;
    const char * type = "message";
    if (message.containing_type() != NULL) {
        const Descriptor & parent ( *message.containing_type() );

        // Find which field we are
        for (int i = 0; i < parent.field_count(); ++i) {
            if (parent.field(i)->message_type() == &message) {
                parentField = parent.field(i);
                break;
            }
        }
        if (parentField->type() == FieldDescriptor::TYPE_GROUP) {
            type = "group";
        }
    }

    // Start printing the message
    printer.Print("/**\n");
    printer.Print(" * `class`\n",
            "class", ClassName(message)
             );
    printer.Print(" *\n");
    printer.Print(" * @`type` `full_name`\n",
            "type", type,
            "full_name", message.full_name()
             );
    printer.Print(" *\n");

    if (moptions.use_single_property()) {
        printer.Print(" * -*- magic properties -*-\n");
        printer.Print(" *\n");
        for (int i = 0; i < message.field_count(); ++i) {
            const FieldDescriptor &field ( *message.field(i) );
            printer.Print(" * @property `type` $`variable`\n",
                    "type", getTypeName(field),
                    "variable", VariableName(field)
                     );
        }
    }

    printer.Print(" */\n");

    printer.Print("class `name`",
            "name", ClassName(message)
             );

    printer.Print(" extends `base`", "base", options.base_class());

    printer.Print("\n{\n");
    printer.Indent();

    if (message.options().HasExtension(php_option)) {
        vector<string> traits;
        vector<string>::iterator it;

        SplitStringUsing(message.options().GetExtension(php_option).trait(), " ", &traits);

        it = traits.begin();
        while (it != traits.end()) {
            printer.Print("use `trait`;\n", "trait", *it);
            ++it;
        }

        printer.Print("\n");
    }

    // Print fields map

    if (moptions.use_single_property()) {
        printer.Print("protected $`var` = array();\n",
            "var",
            moptions.single_property_name()
        );
    } else {
        for (int i = 0; i < message.field_count(); ++i) {
            const FieldDescriptor &field(*message.field(i));

            if (field.is_repeated()) {
                printer.Print("protected $`var` = array();\n",
                    "var", field.name()
                );
            } else {
                printer.Print("protected $`var`;\n",
                    "var", field.name()
                );
            }

            printer.Print("\n");
        }
    }

    printer.Print("\n");

    if (!skip_unknown) {
        // printer.Print("private $_unknown;\n");
    }

    // print the getter methods
    for (int i = 0; i < message.field_count(); ++i) {
        const FieldDescriptor &field(*message.field(i));


        if (options.generate_has()) {
            printer.Print("/**\n");
            printer.Print(" * checking value\n");
            printer.Print(" *\n");
            printer.Print(" * @return bool\n",
                "varname", field.name()
            );
            printer.Print(" */\n");
            printer.Print("public function has`name`()\n",
                "name", UnderscoresToCapitalizedCamelCase(field)
            );
            printer.Print("{\n");
            printer.Indent();

            if (moptions.use_single_property()) {
                printer.Print("if (isset($this->`var`['`key`'])) {\n",
                    "var", moptions.single_property_name(),
                    "key", field.name()
                );
                printer.Indent();
                printer.Print("return true;\n");
                printer.Outdent();
                printer.Print("}\n");
                printer.Print("\n");
                printer.Print("return false;\n");
            } else {
                printer.Print("if (isset($this->`key`)) {\n",
                    "key", field.name()
                );
                printer.Indent();
                printer.Print("return true;\n");
                printer.Outdent();
                printer.Print("}\n");
                printer.Print("\n");
                printer.Print("return false;\n");

            }
            printer.Outdent();
            printer.Print("}\n\n");
        }

        if (options.generate_getter()) {
            printer.Print("/**\n");
            printer.Print(" * getting value\n");
            printer.Print(" *\n");
            printer.Print(" * @return mixed $`varname`\n",
                "varname", field.name()
            );
            printer.Print(" */\n");
            printer.Print("public function get`name`()\n",
                "name", UnderscoresToCapitalizedCamelCase(field)
            );
            printer.Print("{\n");
            printer.Indent();

            if (moptions.use_single_property()) {
                printer.Print("$result = null;\n");
                printer.Print("\n");
                printer.Print("if (array_key_exists('`key`', $this->`var`)) {\n",
                    "key", field.name(),
                    "var", moptions.single_property_name()
                );
                printer.Indent();
                printer.Print("$result = $this->`var`['`key`'];\n",
                    "var", moptions.single_property_name(),
                    "key", field.name()
                );
                printer.Outdent();
                printer.Print("}\n");
                printer.Print("\n");
                printer.Print("return $result;\n");
            } else {
                printer.Print("return $this->`var`;\n",
                    "var",
                    field.name()
                );
            }

            printer.Outdent();
            printer.Print("}\n\n");
        }

        if (options.generate_setter()) {
            printer.Print("/**\n");
            printer.Print(" * setting value\n");
            printer.Print(" *\n");
            printer.Print(" * @property mixed $`varname`\n",
                "varname", field.name()
            );
            printer.Print(" *\n");
            printer.Print(" * @return void\n");
            printer.Print(" */\n");
            if (field.is_repeated()) {
                printer.Print("public function add`name`($`var`)\n",
                    "name", UnderscoresToCapitalizedCamelCase(field),
                    "var", field.name()
                );
            } else {
                printer.Print("public function set`name`($`var`)\n",
                    "name", UnderscoresToCapitalizedCamelCase(field),
                    "var", field.name()
                );
            }
            printer.Print("{\n");
            printer.Indent();

            if (moptions.use_single_property()) {
                if (field.is_repeated()) {
                    printer.Print("$this->`prop`['`key`'][] = $`var`;\n",
                        "prop", moptions.single_property_name(),
                        "key", field.name(),
                        "var", field.name()
                    );
                } else {
                    printer.Print("$this->`prop`['`key`'] = $`var`;\n",
                        "prop", moptions.single_property_name(),
                        "key", field.name(),
                        "var", field.name()
                    );
                }
            } else {
                if (field.is_repeated()) {
                    printer.Print("$this->`key`[] = $`var`;\n",
                        "key", field.name(),
                        "var", field.name()
                    );
                } else {
                    printer.Print("$this->`key` = $`var`;\n",
                        "key", field.name(),
                        "var", field.name()
                    );
                }

            }


            printer.Outdent();
            printer.Print("}\n\n");
        }
    }

    printer.Print("/**\n");
    printer.Print(" * get descriptor for protocol buffers\n");
    printer.Print(" * \n");
    printer.Print(" * @return array\n");
    printer.Print(" */\n");
    printer.Print("public static function getDescriptor()\n");
    printer.Print("{\n");
    printer.Indent();
    printer.Print("static $descriptor;\n");
    printer.Print("\n");
    printer.Print("if (!isset($descriptor)) {\n");
    printer.Indent();
    printer.Print("$desc = new ProtocolBuffersDescriptorBuilder();\n");
    for (int i = 0; i < message.field_count(); ++i) {
        const FieldDescriptor &field (*message.field(i));

        printer.Print("$desc->addField(`tag`, new ProtocolBuffersFieldDescriptor(array(\n",
            "tag",
            SimpleItoa(field.number())
        );
        printer.Indent();
        printer.Print("\"type\"     => `type`,\n",
            "type",
            field_type_to_str(field.type())
        );
        printer.Print("\"name\"     => \"`name`\",\n",
            "name",
            VariableName(field)
        );
        printer.Print("\"required\" => `required`,\n",
            "required",
            (field.is_required()) ? "true" : "false"
        );
        printer.Print("\"optional\" => `optional`,\n",
            "optional",
            (field.is_optional()) ? "true" : "false"
        );
        printer.Print("\"repeated\" => `repeated`,\n",
            "repeated",
            (field.is_repeated()) ? "true" : "false"
        );
        printer.Print("\"packable\" => `packable`,\n",
            "packable",
            (field.is_packed()) ? "true" : "false"
        );
        printer.Print("\"default\"  => `value`,\n",
            "value",
            DefaultValueAsString(field, true)
        );
        if (field.type() == FieldDescriptorProto_Type_TYPE_MESSAGE) {
            const Descriptor &desc(*field.message_type());
            printer.Print("\"message\"  => \"`message`\",\n",
                "message",
                ClassName(desc)
            );
        }
        printer.Outdent();
        printer.Print(")));\n");
    }

    if (moptions.use_single_property()) {
        printer.Print("$phpoptions = $desc->getOptions()->getExtension(ProtocolBuffers::PHP_MESSAGE_OPTION);\n");
        printer.Print("$phpoptions->setUseSingleProperty(true);\n");
        printer.Print("$phpoptions->setSinglePropertyName(\"`name`\");\n",
            "name",
            moptions.single_property_name()
        );

        printer.Print("\n");
    }

    for (int i = 0; i < message.extension_range_count(); ++i) {
        const Descriptor::ExtensionRange &er(*message.extension_range(i));
        printer.Print("$desc->addExtensionRange(`start`, `end`);\n", "start", SimpleItoa(er.start), "end", SimpleItoa(er.end));
    }


    printer.Print("$descriptor = $desc->build();\n");
    printer.Outdent();
    printer.Print("}\n");

    printer.Print("\n");
    printer.Print("return $descriptor;\n");
    printer.Outdent();
    printer.Print("}\n");
    printer.Print("\n");


    // Class Insertion Point
    //	printer.Print(
    //		"\n"
    //		"// @@protoc_insertion_point(class_scope:`full_name`)\n",
    //		"full_name", message.full_name()
    //	);

    printer.Outdent();
    printer.Print("}\n\n");
}

void PHPCodeGenerator::PrintExtension(io::Printer &printer, const FieldDescriptor & e) const {
    //const Descriptor &message(*e->)
    printer.Print("$__extension_registry->add('`message`', `extension`, new ProtocolBuffersFieldDescriptor(array(\n", "message", ClassName(*e.containing_type()), "extension", SimpleItoa(e.number()));
    printer.Indent();
    printer.Print("\"type\"     => `type`,\n",
        "type",
        field_type_to_str(e.type())
    );
    printer.Print("\"name\"     => \"`name`\",\n",
        "name",
        VariableName(e)
    );
    printer.Print("\"required\" => `required`,\n",
        "required",
        (e.is_required()) ? "true" : "false"
    );
    printer.Print("\"optional\" => `optional`,\n",
        "optional",
        (e.is_optional()) ? "true" : "false"
    );
    printer.Print("\"repeated\" => `repeated`,\n",
        "repeated",
        (e.is_repeated()) ? "true" : "false"
    );
    printer.Print("\"packable\" => `packable`,\n",
        "packable",
        (e.is_packed()) ? "true" : "false"
    );
    printer.Print("\"default\"  => `value`,\n",
        "value",
        DefaultValueAsString(e, true)
    );
    if (e.type() == FieldDescriptorProto_Type_TYPE_MESSAGE) {
        const Descriptor &desc(*e.message_type());
        printer.Print("\"message\"  => \"`message`\",\n",
            "message",
            ClassName(desc)
        );
    }
    printer.Outdent();

    printer.Print(")));\n");
}

void PHPCodeGenerator::PrintEnum(io::Printer &printer, const EnumDescriptor & e) const {

    printer.Print("/**\n");
    printer.Print(" * `class`\n",
            "class", ClassName(e)
             );
    printer.Print(" *\n");
    printer.Print(" * @enum `full_name`\n",
            "full_name", e.full_name()
             );
    printer.Print(" */\n");
    printer.Print("class `name`\n{\n", "name", ClassName(e));


    printer.Indent();

    // Print fields
    for (int j = 0; j < e.value_count(); ++j) {
        const EnumValueDescriptor &value ( *e.value(j) );

        printer.Print(
                "const `name` = `number`;\n",
                "name",   UpperString(value.name()),
                "number", SimpleItoa(value.number())
                 );
    }

    printer.Outdent();
    printer.Print("}\n\n");
}

void PHPCodeGenerator::PrintMessages(io::Printer &printer, const FileDescriptor & file) const {
    for (int i = 0; i < file.message_type_count(); ++i) {
        PrintMessage(printer, *file.message_type(i));
    }
}

void PHPCodeGenerator::PrintEnums(io::Printer &printer, const FileDescriptor & file) const {
    for (int i = 0; i < file.enum_type_count(); ++i) {
        PrintEnum(printer, *file.enum_type(i) );
    }
}

void PHPCodeGenerator::PrintExtensions(io::Printer &printer, const FileDescriptor & file) const {
    if (file.extension_count() > 0) {
        printer.Print("$__extension_registry = ProtocolBuffersExtensionRegistry::getInstance();\n");
    }

    for (int i = 0; i < file.extension_count(); ++i) {
        PrintExtension(printer, *file.extension(i));
    }

    if (file.extension_count() > 0) {
        printer.Print("unset($__extension_registry);\n");
    }
}

void PHPCodeGenerator::PrintServices(io::Printer &printer, const FileDescriptor & file) const {
    for (int i = 0; i < file.service_count(); ++i) {
        printer.Print("////\n//TODO Service\n////\n");
    }
}

bool PHPCodeGenerator::Generate(const FileDescriptor* file,
        const string& parameter,
        OutputDirectory* output_directory,
        string* error) const {

    string php_filename ( file->name() + ".php" );

    // Parse the options
    const PHPFileOptions & options(file->options().GetExtension(::php));
    const string & namespace_ (options.namespace_());

    // Generate main file.
    scoped_ptr<io::ZeroCopyOutputStream> output(
            output_directory->Open(php_filename)
            );

    io::Printer printer(output.get(), '`');

    try {
        printer.Print("<?php\n");

        if (!namespace_.empty()) {
            printer.Print("namespace `ns`\n{\n", "ns", namespace_.c_str());
            printer.Indent();
        }

        PrintMessages  (printer, *file);

        PrintEnums     (printer, *file);

        PrintExtensions(printer, *file);

        PrintServices  (printer, *file);

        if (!namespace_.empty()) {
            printer.Outdent();
            printer.Print("}\n");
        }

    } catch (const char *msg) {
        error->assign( msg );
        return false;
    }

    return true;
}


}  // namespace php
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
