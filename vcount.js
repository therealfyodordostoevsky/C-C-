function makeAuthorizedCall (auth) {
    console.log("Calling videos.list...");

    youtube.videos.list({
        auth: auth,
        id: 'dQw4w9WgXcQ',
        part: "id,snippet,statistics",

    }, function(err, response) {
        if (err) {
            console.log('The API returned an error: ' + err);
            return;
        }

        if(response.data.items) {
            if (response.data.items[0]) {
                console.log("Found video. Updating Title...");
                updateVideo(response.data.items[0],auth);
            } else {
                console.log('Zero items in list');
            }
        }
        else {
            console.log('No items found');
            console.log(response);
            return;
        }
    });
}

function updateVideo(video,auth) {
    var viewText = video.statistics.viewCount.toLocaleString();
    video.snippet.title = "This video has " + viewText + " Views";
    console.log("Updating title to " + video.snippet.title + "'");
    console.log(video);
    youtube.videos.update({
        auth: auth,
        part: 'snippet,statistics',
        resource: video,
    },
    function(err, response) {
        if (err) {
            console.log('The API returned an error: ' + err);
            return;
        }
        if(response.data.items) {
            if(response.data.items[0]) {
                console.log("Complete.");
            } else {
                console.log('Zero items in list');
            }
        } else {
            console.log('No items found');
            return;
        }
    });
}