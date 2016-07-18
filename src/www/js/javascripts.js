function topnavbar() {
    document.getElementsByClassName("topnav")[0].classList.toggle("responsive");
}

function load_home() {
	
}

function load_compression() {
	resize_canvas();
}


function resize_canvas(){
	canvas = document.getElementById("plot");
	if (canvas.width  < window.innerWidth) {
		canvas.width  = window.innerWidth;
	}
	if (canvas.height < window.innerHeight) {
		canvas.height = window.innerHeight;
	}
 }
