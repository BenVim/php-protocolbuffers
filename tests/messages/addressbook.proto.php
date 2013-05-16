<?php
/**
 * Tutorial_User
 *
 * @message Tutorial.User
 *
 * -*- magic properties -*-
 *
 * @property int $id
 * @property float $offense
 * @property string $name
 */
class Tutorial_User
{
  protected static $scheme = array(
    'properties' => array(
      'id' => array(
        'type' => 'int',
        'opts' => array(
          'tag' => 1,
        ),
      ),
      'offense' => array(
        'type' => 'float',
        'opts' => array(
          'tag' => 2,
        ),
      ),
      'name' => array(
        'type' => 'string',
        'opts' => array(
          'tag' => 3,
        ),
      ),
    ),
    'scheme' => array(
      1 => array(
        'name'     => 'id',
        'type'     => 5,
        'required' => true,
        'optional' => false,
        'repeated' => false,
        'packable' => false,
        'default'  => null,
      ),
      2 => array(
        'name'     => 'offense',
        'type'     => 2,
        'required' => false,
        'optional' => true,
        'repeated' => false,
        'packable' => false,
        'default'  => null,
      ),
      3 => array(
        'name'     => 'name',
        'type'     => 9,
        'required' => false,
        'optional' => true,
        'repeated' => false,
        'packable' => false,
        'default'  => null,
      ),
    ),
  );

  public function getId()
  {
    $result = null;

    if (array_key_exists('id', $this->_properties)) {
      $result = $this->_properties['id'];
    }

    return $result;
  }

  public function setId($id)
  {
    $this->_properties['id'] = $id;
  }

  public function getOffense()
  {
    $result = null;

    if (array_key_exists('offense', $this->_properties)) {
      $result = $this->_properties['offense'];
    }

    return $result;
  }

  public function setOffense($offense)
  {
    $this->_properties['offense'] = $offense;
  }

  public function getName()
  {
    $result = null;

    if (array_key_exists('name', $this->_properties)) {
      $result = $this->_properties['name'];
    }

    return $result;
  }

  public function setName($name)
  {
    $this->_properties['name'] = $name;
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

/**
 * Tutorial_AddressBook
 *
 * @message Tutorial.AddressBook
 *
 * -*- magic properties -*-
 *
 * @property array $user
 */
class Tutorial_AddressBook
{
  protected static $scheme = array(
    'properties' => array(
      'user' => array(
        'type' => 'array',
        'opts' => array(
          'tag' => 1,
        ),
      ),
    ),
    'scheme' => array(
      1 => array(
        'name'     => 'user',
        'type'     => 11,
        'required' => false,
        'optional' => false,
        'repeated' => true,
        'packable' => false,
        'default'  => null,
        'message'  => 'Tutorial_User',
      ),
    ),
  );

  public function getUser()
  {
    $result = null;

    if (array_key_exists('user', $this->_properties)) {
      $result = $this->_properties['user'];
    }

    return $result;
  }

  public function addUser($user)
  {
    $this->_properties['user'][] = $user;
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

