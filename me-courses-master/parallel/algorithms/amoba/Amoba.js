// Table size
var width;
var height;

// Map for calculations
var Map = new Array();

// Map size
var Map_width;
var Map_start;
var Map_length;

// Gamer code { 1 -> X, 2 -> O }
var Gamer = 1;

// Winner of game { 0 -> nobody, 1 -> X, 2 -> O }
var Winner;

//---------------------------
function setSign(id, player){
//---------------------------
	switch(player){
		case 1:
			document.getElementById("cell"+id).className = "sign_X";
			break;			
		case 2:
			document.getElementById("cell"+id).className = "sign_O";
			break;			
		case 3:
			document.getElementById("cell"+id).className = "winner_X";
			break;			
		case 4:
			document.getElementById("cell"+id).className = "winner_O";
			break;			
	}
}

//---------------------
function createTable(){
//---------------------

	width = 20;
	height = 20;

	// ??? {
	width_temp = document.getElementById("columnNum").value;
	height_temp = document.getElementById("rowNum").value;

	width += width_temp - 20;
	height += height_temp - 20;
	// }
	
	Winner = 0;

	// Create Map
	Map_width = width + 2;
	Map_start = 2 * Map_width + 3;
	Map_length = (height + 4) * Map_width + 2;

	for(i=0; i<Map_length; i++) Map[i] = 3;

	n = Map_start;
	for(k=0; k<height; k++){
		for(i=0; i<width; i++){
			Map[n] = 0;
			n++;
		}
		n += 2;
	}

	// Set sign
	sign = "X";
	if(Gamer == 2) sign = "O";

	// Create table
	inner = "<table>";

	cellIndex = Map_start;
	for(y=1; y<=height; y++){
		inner += "<tr>";
		for (x=1; x<=width; x++){

			inner += "<td class='empty_"+sign+"' id='cell" + cellIndex + "' ";
			inner += "onClick='clickTable("+cellIndex+");'></td>";

			cellIndex++;
		}
		inner += "</tr>";
		cellIndex += 2;
	}
	inner += "</table>";

	document.getElementById("AmobaTable").innerHTML = inner;

	// First step
	if(document.getElementById("first").value==2) calculate();
}

//----------------------
function clickTable(id){
//----------------------
	if(Winner == 0 && Map[id] == 0){
		setSign(id, Gamer);
		Map[id] = Gamer;

		if(isFinal(id)){
			Winner = Gamer;
		}else{
			calculate();
		}
	}
}

//------------------
function swapSign(){
//------------------
	// Change gamer index
	Gamer = 3 - Gamer;

	// Change pictures on menu panel	
	if(Gamer == 1){
		document.getElementById("gamerSign").className = "sign_X";
		document.getElementById("compSign").className = "sign_O";
	}
	else {
		document.getElementById("gamerSign").className = "sign_O";
		document.getElementById("compSign").className = "sign_X";
	}

	// Swap images on Map
	n = Map_start;
	for(k=0; k<height; k++){
		for(i=0; i<width; i++){
			if(Map[n] == 0){
				if(Gamer == 1){
					document.getElementById("cell"+n).className = "empty_X";
				}
				else {
					document.getElementById("cell"+n).className = "empty_O";
				}
			}
			else if(Map[n] > 2){
				Map[n] = 7 - Map[n];
				setSign(n, Map[n]);
			}
			else {
				Map[n] = 3 - Map[n];
				setSign(n, Map[n]);
			}
			n++;
		}
		n += 2;
	}
}

//---------------------------
function calcStar(n, player){
//---------------------------
	// n      - center coordinate
	// player - player number { X -> 1, O -> 2 }

	var Direction = [1, Map_width-1, Map_width, Map_width+1];

	// Symbol :: 0 - empty, 1 - player X, 2 - player O, 3 - wall
	var Symbol = new Array();

	var Value = [1, 2, 6, 20, 4000];

	var Sum = 0;

	for(d=0; d<4; d++){ // calculate in d direction

		a = b = n; // set pointer to center

		for(j=0; j<4; j++) Symbol[j] = 0; // zeros all Symbol count

		Symbol[0]++; // the center field is empty

		for(j=0; j<4; j++){
			b -= Direction[d]; // move back with b pointer
			Symbol[Map[b]]++; // count Symbols
		}

		// Add current values to Sum
		do {
			if(Symbol[player] + Symbol[0] == 5){
				Sum += Value[Symbol[player]];
			}
			
			if(Symbol[3 - player] + Symbol[0] == 5){
				Sum += Value[Symbol[3 - player]];
			}

			a += Direction[d];
			Symbol[Map[a]]++;
			Symbol[Map[b]]--;
			b += Direction[d];

		} while(b <= n);
	}

	return Sum;
}

//-------------------
function calculate(){
//-------------------
	var sum = 0;  // sum of actual field
	var max = -9999;  // index of field with maximal value
	var Steps = new Array(); // optimal steps

	n = Map_start;
	for(k=0; k<height; k++){
		for(i=0; i<width; i++){
			if(Map[n] == 0){
				sum = calcStar(n, 3-Gamer);
				if(sum > max){
					Steps.length = 0;
					Steps[0] = n;
					max = sum;
				}
				else if(sum == max){
					Steps.push(n);
				}
			}
			n++;
		}
		n += 2;
	}

	// Switch one from optional steps randomly
	step = Steps[Math.floor(Math.random()*(Steps.length))];

	Map[step] = 3-Gamer;
	setSign(step, 3-Gamer);
	
	if(isFinal(step) == true){
		Winner = 3-Gamer;
	}
}

//------------------
function isFinal(n){
//------------------
	var player = Map[n];

	var Direction = [1, Map_width-1, Map_width, Map_width+1];
	var Symbol = new Array();

	for(d=0; d<4; d++){ // calculate in d direction

		a = b = n; // set pointer to center

		for(j=0; j<4; j++) Symbol[j] = 0; // zeros all Symbol count

		Symbol[player]++; // the center field is the player

		for(j=0; j<4; j++){
			b -= Direction[d]; // move back with b pointer
			Symbol[Map[b]]++; // count Symbols
		}

		do {
			if(Symbol[player] == 5){
				// (player) WIN !!!
				for(i=0; i<5; i++){
					Map[b] += 2;
					setSign(b, Map[b]);
					b += Direction[d];
				}

				return true;
			}

			if(Symbol[3 - player] == 5){
				// (3 - player) WIN !!!
				for(i=0; i<5; i++){
					Map[b] += 2;
					setSign(b, Map[b]);
					b += Direction[d];
				}

				return true;
			}

			a += Direction[d];
			Symbol[Map[a]]++;
			Symbol[Map[b]]--;
			b += Direction[d];

		} while(b <= n);
	}

	return false;
}

