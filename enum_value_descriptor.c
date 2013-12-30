#include "protocolbuffers.h"
#include "enum_value_descriptor.h"

/* {{{ proto void ProtocolBuffersEnumValueDescriptor::__construct()
*/
PHP_METHOD(protocolbuffers_enum_value_descriptor, __construct)
{
	zval *instance = getThis();
	zval *value;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"a", &value) == FAILURE) {
		return;
	}
}
/* }}} */


static zend_function_entry protocolbuffers_enum_value_descriptor_methods[] = {
	PHP_ME(protocolbuffers_enum_value_descriptor, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_FE_END
};

void php_protocolbuffers_enum_value_descriptor_class(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "ProtocolBuffersEnumValueDescriptor", protocolbuffers_enum_value_descriptor_methods);
	php_protocol_buffers_enum_value_descriptor_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	PHP_PROTOCOLBUFFERS_REGISTER_NS_CLASS_ALIAS(PHP_PROTOCOLBUFFERS_NAMESPACE, "EnumValueDescriptor", php_protocol_buffers_enum_value_descriptor_class_entry);

	zend_declare_property_string(php_protocol_buffers_enum_value_descriptor_class_entry, ZEND_STRS("name")-1, "", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_long(php_protocol_buffers_enum_value_descriptor_class_entry, ZEND_STRS("value")-1, 0, ZEND_ACC_PROTECTED TSRMLS_CC);

}
