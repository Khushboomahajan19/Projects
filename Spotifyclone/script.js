console.log("Welcome to spotify");
// let audioElement = new Audio("Unstoppable(PaglaSongs).mp3");
let songIndex = 0;
let audioElement = new Audio("1.mp3.mp3");
let masterPlay = document.getElementById("masterPlay");
let myProgressbar = document.getElementById("myProgressbar");
let masterSongName = document.getElementById("masterSongName");
// let gif = document.getElementById("gif");
let songItems = Array.from(document.getElementsByClassName("songItem"));
let songs = [
  {
    songName: "Unstoppable",
    filepath: "1.mp3.mp3",
    coverPath: "covers/1.jpg",
  },
  {
    songName: "Calm down",
    filepath: "2.mp3.mp3",
    coverPath: "covers/1.jpg",
  },
  {
    songName: "Cheap Thrils",
    filepath: "3.mp3.mp3",
    coverPath: "covers/1.jpg",
  },
  {
    songName: "Friends",
    filepath: "4.mp3.mp3",
    coverPath: "covers/1.jpg",
  },
  {
    songName: "Copines",
    filepath: "5.mp3.mp3",
    coverPath: "covers/1.jpg",
  },
  {
    songName: "Love Nwantiti",
    filepath: "6.mp3.mp3",
    coverPath: "covers/1.jpg",
  },
  {
    songName: "Go down deh",
    filepath: "7.mp3.mp3",
    coverPath: "covers/1.jpg",
  },
  {
    songName: "This is what you came for",
    filepath: "8.mp3.mp3",
    coverPath: "covers/1.jpg",
  },
  {
    songName: "People",
    filepath: "9.mp3.mp3",
    coverPath: "covers/1.jpg",
  },
];
songItems.forEach((element, i) => {
  // console.log(element, i);
  element.getElementsByTagName("img")[0].src = songs[i].coverPath;
  element.getElementsByClassName("songName")[0].innerText = songs[i].songName;
});
//audioelement.play()
//Handle play/pause click
masterPlay.addEventListener("click", () => {
  if (audioElement.paused || audioElement.currentTime <= 0) {
    audioElement.play();
    masterPlay.classList.remove("fa-play-circle");
    masterPlay.classList.add("fa-pause-circle");
    // gif.style.opacity = 1;
  } else {
    audioElement.pause();
    masterPlay.classList.remove("fa-pause-circle");
    masterPlay.classList.add("fa-play-circle");
    gif.style.opacity = 0;
  }
});
audioElement.addEventListener("timeupdate", () => {
  // console.log("timeupdate");
  //Update seekbar
  let progress = parseInt(
    (audioElement.currentTime / audioElement.duration) * 100
  );
  // console.log(progress);
  myProgressbar.value = progress;
});
myProgressbar.addEventListener("change", () => {
  audioElement.currentTime = myProgressbar.value * audioElement.duration;
});
const makeAllPlays = () => {
  Array.from(document.getElementsByClassName("songItemPlay")).forEach(
    (element) => {
      element.classList.remove("fa-pause-circle");
      element.classList.add("fa-play-circle");
    }
  );
};
Array.from(document.getElementsByClassName("songItemPlay")).forEach(
  (element) => {
    element.addEventListener("click", (e) => {
      // console.log(e.target);
      makeAllPlays();
      songIndex = parseInt(e.target.id);
      e.target.classList.remove("fa-play-circle");
      e.target.classList.add("fa-pause-circle");
      audioElement.src = `${songIndex + 1}.mp3.mp3`;
      masterSongName.innerText = songs[songIndex].songName;
      audioElement.currentTime = 0;
      audioElement.play();
      masterPlay.classList.remove("fa-play-circle");
      masterPlay.classList.add("fa-pause-circle");
    });
  }
);
document.getElementById("next").addEventListener("click", () => {
  if (songIndex >= 9) {
    songIndex = 0;
  } else {
    songIndex += 1;
  }
  audioElement.src = `${songIndex + 1}.mp3.mp3`;
  masterSongName.innerText = songs[songIndex].songName;
  audioElement.currentTime = 0;
  audioElement.play();
  masterPlay.classList.remove("fa-play-circle");
  masterPlay.classList.add("fa-pause-circle");
});

document.getElementById("previous").addEventListener("click", () => {
  if (songIndex <= 0) {
    songIndex = 0;
  } else {
    songIndex -= 1;
  }
  audioElement.src = `${songIndex + 1}.mp3.mp3`;
  masterSongName.innerText = songs[songIndex].songName;
  audioElement.currentTime = 0;
  audioElement.play();
  masterPlay.classList.remove("fa-play-circle");
  masterPlay.classList.add("fa-pause-circle");
});
