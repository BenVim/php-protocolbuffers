<?php
/**
 * Tutorial_Fixed32
 *
 * @message Tutorial.Fixed32
 *
 * -*- magic properties -*-
 *
 * @property array $value
 */
class Tutorial_Fixed32
{
  protected static $descriptor;

  protected $_properties = array();

  protected $value = array();

  public function getValue()
  {
    return $this->value;
  }

  public function addValue($value)
  {
    $this->value[] = $value;
  }

  /**
   * get descriptor for protocol buffers
   * 
   * @return array
   */
  public static function getDescriptor()
  {
      if (!isset(self::$descriptor)) {
          $desc = new ProtocolBuffers_DescriptorBuilder();
          $desc->addField(1, new ProtocolBuffers_FieldDescriptor(array(
              "type"     => ProtocolBuffers::TYPE_FIXED32,
              "name"     => "value",
              "packable" => true,
              "repeated" => true,
              "default"  => null,
          )));

          self::$descriptor = $desc->build();
      }

      return self::$descriptor;

  }

}

