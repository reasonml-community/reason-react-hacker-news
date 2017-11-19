let apiBaseUrl = "https://serverless-api.hackernewsmobile.com/";

let topStoriesUrl = (page) => apiBaseUrl ++ ("topstories-25-" ++ (string_of_int(page) ++ ".json"));

let storyUrl = (id) => apiBaseUrl ++ ("stories/" ++ (string_of_int(id) ++ ".json"));

type story = {
  by: string,
  descendants: int,
  id: int,
  score: int,
  time: int,
  title: string,
  url: option(string)
};

type comment_deleted = {id: int};

type comment_present = {
  by: string,
  id: int,
  kids: option(array(int)),
  parent: int,
  text: option(string),
  time: int
};

type comment =
  | CommentPresent(comment_present)
  | CommentDeleted(comment_deleted);

type comments_map = JSMap.map(int, comment);

type story_with_comments = {
  by: string,
  descendants: int,
  id: int,
  kids: option(array(int)),
  score: int,
  time: int,
  title: string,
  url: option(string),
  descendentIds: array(int),
  comments: comments_map
};

type topstories = array(story);

let parseIdsArray = (json) : array(int) => Json.Decode.(json |> array(int));

let getCommentId = (comment) =>
  switch comment {
  | CommentDeleted(c) => c.id
  | CommentPresent(c) => c.id
  };

let parseComment = (json) : comment => {
  let deletedMaybe = Json.Decode.(json |> optional(field("deleted", bool)));
  let deleted =
    switch deletedMaybe {
    | Some(v) => v == true
    | None => false
    };
  if (deleted) {
    CommentDeleted(Json.Decode.{id: json |> field("id", int)})
  } else {
    CommentPresent(
      Json.Decode.{
        by: json |> field("by", string),
        id: json |> field("id", int),
        parent: json |> field("parent", int),
        kids: json |> optional(field("kids", parseIdsArray)),
        text: json |> optional(field("text", string)),
        time: json |> field("time", int)
      }
    )
  }
};

let parseCommentsArray = (json) : comments_map => {
  let commentsArray = Json.Decode.(json |> array(parseComment));
  let commentsArrayOfPairs =
    Array.map((comment: comment) => (getCommentId(comment), comment), commentsArray);
  JSMap.create(commentsArrayOfPairs)
};

let parseStoryWithComments = (json) : story_with_comments =>
  Json.Decode.{
    by: json |> field("by", string),
    descendants: json |> field("descendants", int),
    descendentIds: json |> field("descendentIds", parseIdsArray),
    comments: json |> field("comments", parseCommentsArray),
    id: json |> field("id", int),
    kids: json |> optional(field("kids", parseIdsArray)),
    score: json |> field("score", int),
    time: json |> field("time", int),
    title: json |> field("title", string),
    url: json |> optional(field("url", string))
  };

let parseStory = (json) : story =>
  Json.Decode.{
    by: json |> field("by", string),
    descendants: json |> field("descendants", int),
    id: json |> field("id", int),
    score: json |> field("score", int),
    time: json |> field("time", int),
    title: json |> field("title", string),
    url: json |> optional(field("url", string))
  };

let parseStories = (json) : array(story) => Json.Decode.(json |> array(parseStory));

let fetchTopStories = (page, callback) =>
  Js.Promise.(
    Bs_fetch.fetch(topStoriesUrl(page))
    |> then_(Bs_fetch.Response.text)
    |> then_(
         (text) =>
           Js.Json.parseExn(text)
           |> parseStories
           |> (
             (stories) => {
               callback((page, stories));
               resolve(None)
             }
           )
       )
  );

let fetchStoryWithComments = (id, callback) =>
  Js.Promise.(
    Bs_fetch.fetch(storyUrl(id))
    |> then_(Bs_fetch.Response.text)
    |> then_(
         (text) =>
           Js.Json.parseExn(text)
           |> parseStoryWithComments
           |> (
             (stories) => {
               callback(stories);
               resolve(None)
             }
           )
       )
  );
