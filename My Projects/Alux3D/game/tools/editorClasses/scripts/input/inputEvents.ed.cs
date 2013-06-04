// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

///
/// Returns Projects API's EventManager Singleton
///
function Input::GetEventManager()
{
   if( !isObject( $_Tools::InputEventManager ) )
      $_Tools::InputEventManager = new EventManager() { queue = "InputEventManager"; };
      
   return $_Tools::InputEventManager;
}
