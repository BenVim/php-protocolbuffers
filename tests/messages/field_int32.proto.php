<?php
/**
 * Tutorial_Integer32
 *
 * @message Tutorial.Integer32
 *
 * -*- magic properties -*-
 *
 * @property int $value
 */
class Tutorial_Integer32
{
  protected static $descriptor;

  protected $_properties = array();

  protected $value;

  public function getValue()
  {
    return $this->value;
  }

  public function setValue($value)
  {
    $this->value = $value;
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
              "type"     => ProtocolBuffers::TYPE_INT32,
              "name"     => "value",
              "packable" => false,
              "repeated" => false,
              "default"  => null,
          )));

          self::$descriptor = $desc->build();
      }

      return self::$descriptor;

  }

}

