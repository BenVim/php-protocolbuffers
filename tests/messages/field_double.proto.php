<?php
/**
 * Tutorial_Double
 *
 * @message Tutorial.Double
 *
 * -*- magic properties -*-
 *
 * @property float $value
 */
class Tutorial_Double
{
  protected static $scheme = array(
    'properties' => array(
      'value' => array(
        'type' => 'float',
        'opts' => array(
          'tag' => 1,
        ),
      ),
    ),
    'scheme' => array(
      1 => array(
        'name'     => 'value',
        'type'     => 2,
        'required' => true,
        'optional' => false,
        'repeated' => false,
        'packable' => false,
        'default'  => null,
      ),
    ),
  );

  public function getValue()
  {
    $result = null;

    if (array_key_exists('value', $this->_properties)) {
      $result = $this->_properties['value'];
    }

    return $result;
  }

  public function setValue($value)
  {
    $this->_properties['value'] = $value;
  }

  /**
   * get descriptor for protocol buffers
   * 
   * @return array
   */
  public static function getDescriptor()
  {
    return self::$scheme['scheme'];
  }

}

