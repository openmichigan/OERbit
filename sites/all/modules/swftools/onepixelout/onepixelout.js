// Array to hold the player object ids
onepixelout_objects = new Array();

// Array to hold the playerIDs
onepixelout_players = new Array();

// Set a flag to show if id's have been collected
onepixelout_initialized = 0;

// Call back when a player is started - it uses the flashvar playerID of the player that is starting as its parameter
function ap_stopAll(playerID) {
  
  // If this is the first time we clicked a player then get the object and player ids
  if (!onepixelout_initialized) {
    onepixelout_getPlayers();
    onepixelout_initialized = 1;
  }
  
  // Iterate over the array of players
  for(var i = 0; i < onepixelout_players.length; i++) {
    
    try {
  
    // If this player id is not the playerID that is starting then close it
      if(onepixelout_players[i] != playerID) {
        document.getElementById(onepixelout_objects[i]).SetVariable('closePlayer', 1);
      }
      else {
        document.getElementById(onepixelout_objects[i]).SetVariable('closePlayer', 0);
      }
    } catch( errorObject ) {
     // Trap any errors
    }
  }
}


// Get object and playerIDs of onepixelout players
function onepixelout_getPlayers() {

  //Initialize a counter
  i = 0;
  
  // Iterate over all onepixelout players
  $('.onepixelout > [id^=swf]').each(function () {
    
    // Collect the div ids, turn them in to object ids, and store them
    onepixelout_objects[i] = $(this).attr('id');
    
    // Extract the flashvars string
    flashvars = $('#' + onepixelout_objects[i] + ' > param').filter('[name=flashvars]').attr('value');

    // Find out where playerID appears in the value
    index1 = flashvars.indexOf('playerID');
    
    // Find out where the first ampersand is in the value
    index2 = flashvars.indexOf('&');
    
    // The playerID variable is this substring so store it
    onepixelout_players[i++] = flashvars.substring(index1 + 9, index2);
  
  });
  
}
