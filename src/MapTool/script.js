
var res = {
	img: {}
};

function loadData() {
	var data = [
		"tile.png"
		,"turntable.png"
		];
	data.forEach(function(img_name){
		res.img[img_name] = new Image();
		res.img[img_name].src = "image/" + img_name;
	});
}


//----------------------------------------[Game]----------------------------------------

var canv, g;
var show_grid = true;

var TILE_MODE = 0;
var AREA_MODE = 1;
var edit_mode = TILE_MODE;

var key = {
	state: [],
	now: [],
	old: [],
	update: function(){this.old = this.now.slice(0);this.now = this.state.slice(0);},
	isTriggered: function(key){return !this.old[key]&&this.now[key]},
	isPressed: function(key){return this.now[key];},
	isReleased: function(key){return this.old[key]&&!this.now[key];}
};

var mouse = {
	state: [],
	now: [],
	old: [],
	x: 0,
	y: 0,
	// keycode : left 0, right 2
	update: function(){this.old = this.now.slice(0);this.now = this.state.slice(0);},
	isTriggered: function(key){return !this.old[key]&&this.now[key]},
	isPressed: function(key){return this.now[key]},
	isReleased: function(key){return this.old[key]&&!this.now[key]}
};

function init() {
	canv = document.getElementById("canv");
	g = canv.getContext('2d');

	window.addEventListener('keydown', function(event) { key.state[event.keyCode] = true; });
	window.addEventListener('keyup', function(event) { key.state[event.keyCode] = false; });

	canv.addEventListener('mouseup', function(event) { mouse.state[event.button] = false; });
	canv.addEventListener('mousedown', function(event) { mouse.state[event.button] = true; });
	canv.addEventListener('mousemove', function(event) { mouse.x = event.layerX; mouse.y = event.layerY; });

	loadData();
	resetTile();

	setInterval(gameLoop, Math.round(1000/60));
}

function gameLoop() {
	g.clearRect(0,0,canv.width,canv.height);
	
	key.update();
	mouse.update();
	
	inputProc();
	update();
	draw();

/*
	g.fillStyle = "black";
	g.font = "12px Arial";
	g.fillText("("+mouse.x+", "+mouse.y+")", 10, 15);

	var a = getTileXY(mouse.x, mouse.y);
	g.fillStyle = "black";
	g.font = "12px Arial";
	g.textAlign = "left";
	g.fillText("("+a.x+", "+a.y+")", 10, 30);
*/
}

function inputProc() {
	switch (edit_mode)
	{
	case TILE_MODE:
		editTileInputProc();
		break;
	case AREA_MODE:
		editAreaInputProc();
		break;
	}

	if (key.isTriggered('R'.charCodeAt(0))) {
		resetTile();
		resetArea();
	}
	else if (key.isTriggered('S'.charCodeAt(0))) {
		saveStageData();
	}
	else if (key.isTriggered('O'.charCodeAt(0))) {
		loadStageData();
	}
	else if (key.isTriggered('G'.charCodeAt(0))) {
		show_grid = !show_grid;
	}

	else if (key.isTriggered('1'.charCodeAt(0))) {
		edit_mode = TILE_MODE;
	}
	else if (key.isTriggered('2'.charCodeAt(0))) {
		edit_mode = AREA_MODE;
	}
}

function update() {
}

function draw() {
	if (tile_select_mode) {
		drawPalette();
		drawGrid();
	}
	else {
		drawArea();
		drawTile();

		if (show_grid)
			drawGrid();
	}

	switch (edit_mode)
	{
	case TILE_MODE:
		g.globalAlpha = 0.75;
		drawTileImage(cursor_tile_id, mouse.x - tile_size/2, mouse.y - tile_size/2);
		g.globalAlpha = 1;
		break;
	case AREA_MODE:
		g.globalAlpha = 0.75;
		drawAreaImage(cursor_area.img, mouse.x, mouse.y, cursor_area.width, cursor_area.height);
		g.globalAlpha = 1;
		break;
	}

}

var tile_size = 16;

function drawGrid() {
	g.beginPath();

	for (var x = tile_size; x < canv.width; x += tile_size) {
		g.moveTo(x, 0);
		g.lineTo(x, canv.height);
	}
	for (var y = tile_size; y < canv.height; y += tile_size) {
		g.moveTo(0, y);
		g.lineTo(canv.width, y);
	}

	g.strokeStyle = "black";
	g.globalAlpha = 0.5;
	g.stroke();
	g.globalAlpha = 1;
}

//----------------------------------------[Stage]----------------------------------------

function loadStageData() {
	var data = prompt("JSON을 복붙하시오.");
	if (!data) return;
	var o = JSON.parse(data);
	tiles = o.tile.tiles;
	areas = o.area;
}

function saveStageData() {
	var o = {
		tile: {
			width: tile_w,
			height: tile_h,
			tiles: tiles
		},
		area: areas
	};
	prompt("복사하시오.", JSON.stringify(o));
}

//----------------------------------------[Tile]----------------------------------------

var tiles = [];
var tile_w = 480/tile_size;
var tile_h = 640/tile_size;
var tile_num = tile_w * tile_h;

var tile_img_w = 256/tile_size;
var tile_img_h = 256/tile_size;
var tile_img_num = tile_img_w * tile_img_h;

var cursor_tile_id = 1;

var tile_select_mode = false;

function resetTile() {
	tiles = [];
	for (var i = 0; i < tile_num; ++i)
		tiles.push(0);
}

function drawTile() {
	
	g.globalAlpha = 0.5;
	for (var i = 0; i < tile_num; ++i) {
		var x = i % tile_w;
		var y = Math.floor(i / tile_w);
		drawTileImage(tiles[i], x*tile_size + 5, y*tile_size + 5);
	}
	g.globalAlpha = 1;
	
	for (var i = 0; i < tile_num; ++i) {
		var x = i % tile_w;
		var y = Math.floor(i / tile_w);
		drawTileImage(tiles[i], x*tile_size, y*tile_size);
/*
		g.fillStyle = "grey";
		g.font = "12px Arial";
		g.textBaseline = "top";
		g.fillText(tiles[i], 2 + x*40, y*40);
		g.textBaseline = "alphabetic";
*/
	}
}

function drawPalette() {
	for (var i = 0; i < tile_img_num; ++i) {
		var x = i % tile_img_w;
		var y = Math.floor(i / tile_img_w);
		drawTileImage(i, x*tile_size, y*tile_size);
	}
}

function drawTileImage(id, x, y) {
	var sx = id % tile_img_w;
	var sy = Math.floor(id / tile_img_w);
	g.drawImage(res.img["tile.png"], sx*tile_size, sy*tile_size, tile_size, tile_size, x, y, tile_size, tile_size);
}

function getTileXY(mouse_x, mouse_y) {
	var x = mouse_x;
	var y = mouse_y;
	return {x: Math.floor(x/tile_size), y: Math.floor(y/tile_size)};
}

function getTileID(x, y) {
	if (x >= tile_w)
		x = tile_w - 1;
	if (y >= tile_h)
		y = tile_h - 1;
	return x + y*tile_w;
}


function editTileInputProc() {
	if (mouse.isPressed(0)) {
		var coord = getTileXY(mouse.x, mouse.y);
		var id = getTileID(coord.x, coord.y);

		if (tile_select_mode) {
			id = coord.x + coord.y * tile_img_w;
			if (id < tile_img_num)
				cursor_tile_id = id;
		}
		else {
			tiles[id] = cursor_tile_id;
		}
	}
	else if (mouse.isPressed(2)) {
		var coord = getTileXY(mouse.x, mouse.y);
		var id = getTileID(coord.x, coord.y);
		if (tile_select_mode) {
			if (id < tile_img_num)
				cursor_tile_id = id;
		}
		else {
			cursor_tile_id = tiles[id];
		}
	}

	tile_select_mode = key.isPressed(32);
}

//----------------------------------------[Area]----------------------------------------

var areas = [];

var AREA_TURNTABLE = "turntable";
var cursor_area = {
	type: AREA_TURNTABLE
	, width: 100
	, height: 100
	, img: AREA_TURNTABLE + ".png"
}

function resetArea() {
	areas = [];
}

function drawArea() {
	areas.forEach(function(area){
		drawAreaImage(area.img, area.pos[0], area.pos[1], area.width, area.height);
	});
}

function drawAreaImage(src, x, y, w, h) {
	var img = res.img[src];
	g.drawImage(img, x - w/2, y - h/2, w, h);
}

function getAreaObject(x, y) {
	for (var i = 0; i < areas.length; ++i) {
		if (areas[i].checkRect(x, y)) {
			return areas[i];
		}
	}
	return null;
}

function editAreaInputProc() {
	if (mouse.isTriggered(0)) {
		var area = null;
		switch (cursor_area.type)
		{
		case AREA_TURNTABLE:
			area = AreaObject.makeTurntable(mouse.x, mouse.y, cursor_area.width/2, false);
			break;
		};
		if (area) {
			areas.push(area);
		}
	}
	else if (mouse.isTriggered(2)) {
		for (var i = 0; i < areas.length; ++i) {
			if (areas[i].checkRect(mouse.x, mouse.y)) {
				areas.splice(i, 1);
				break;
			}
		}
	}

	if (key.isTriggered(219)) {			// [
		if (cursor_area.width > 10 || cursor_area.height > 10) {
			cursor_area.width -= 10;
			cursor_area.height -= 10;
		}
		else {
			cursor_area.width = 10;
			cursor_area.height = 10;
		}
	}
	else if (key.isTriggered(221)) {	// ]
		cursor_area.width += 10;
		cursor_area.height += 10;
	}
}

function AreaObject(type, x, y, width, height, subtype, img) {
	this.type = type;
	this.pos = [x, y];
	this.width = width;
	this.height = height;
	this.subtype = subtype;
	this.img = img;
}

AreaObject.makeTurntable = function(x, y, radius, ccw){
	var subtype = ccw? "ccw" : "cw";
	return new AreaObject(AREA_TURNTABLE, x, y, radius*2, radius*2, subtype, AREA_TURNTABLE + ".png");
};

AreaObject.prototype.checkRect = function(x, y){
	return Math.abs(this.pos[0] - x)*2 < this.width &&
		Math.abs(this.pos[1] - y)*2 < this.height;
};