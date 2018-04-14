/* https://github.com/tastejs/hacker-news-pwas/blob/master/docs/api.md */
let apiBaseUrl = "https://api.hnpwa.com/v0";

let topStoriesUrl = page => {j|$apiBaseUrl/newest/$page.json|j};
let newsStoriesUrl = page => {j|$apiBaseUrl/news/$page.json|j};
let askStoriesUrl = page => {j|$apiBaseUrl/ask/$page.json|j};
let showStoriesUrl = page => {j|$apiBaseUrl/show/$page.json|j};
let jobStoriesUrl = page => {j|$apiBaseUrl/show/$page.json|j};

type story = {
  id: int,
  title: string,
  points: option(int),
  user: option(string),
  time: int,
  time_ago: string,
  comments_count: int,
  story_type: string,
  url: option(string),
  domain: option(string)
};

type stories = array(story);

let itemUrl = id => {j|$apiBaseUrl/item/$id.json|j};

type story_with_comments = {
  id: int,
  title: string,
  points: option(int),
  user: option(string),
  time: int,
  time_ago: string,
  content: string,
  deleted: option(bool),
  dead: option(bool),
  story_type: string,
  url: option(string),
  domain: option(string),
  comments: array(story_with_comments),
  level: int,
  comments_count: int
};

let userUrl = id => {j|$apiBaseUrl/user/$id.json|j};

type user = {
  about: option(string),
  created_time: int,
  created: string,
  id: string,
  karma: int
};

module Decode = {
  let rec storyWithComments = (json) : story_with_comments => {
    Json.Decode.{
      id: json |> field("id", int),
      title: json |> field("title", string),
      points: json |> optional(field("points", int)),
      user: json |> optional(field("user", string)),
      time: json |> field("time", int),
      time_ago: json |> field("time_ago", string),
      content: json |> field("content", string),
      deleted: json |> optional(field("deleted", bool)),
      dead: json |> optional(field("dead", bool)),
      story_type: json |> field("type", string),
      url: json |> optional(field("url", string)),
      domain: json |> optional(field("domain", string)),
      comments: json |> field("comments", array(storyWithComments)),
      level: json |> field("level", int),
      comments_count: json |> field("comments_count", int),
    }
  };

  let story = (json) : story =>
    Json.Decode.{
      id: json |> field("id", int),
      title: json |> field("title", string),
      points: json |> optional(field("points", int)),
      user: json |> optional(field("user", string)),
      time: json |> field("time", int),
      time_ago: json |> field("time_ago", string),
      comments_count: json |> field("comments_count", int),
      story_type: json |> field("type", string),
      url: json |> optional(field("url", string)),
      domain: json |> optional(field("domain", string))
    };

  let stories = (json) : array(story) =>
    Json.Decode.(json |> array(story));
};

let fetchTopStories = (page, callback) =>
  Js.Promise.(
    Fetch.fetch(topStoriesUrl(page+1))
    |> then_(Fetch.Response.json)
    |> then_(json =>
        json  |> Decode.stories
              |> stories => {
                   callback((page, stories));
                   resolve(())
                 }
       )
    |> ignore /* TODO: error handling */
  );

let fetchStoryWithComments = (id, callback) =>
  Js.Promise.(
    Fetch.fetch(itemUrl(id))
    |> then_(Fetch.Response.json)
    |> then_(json =>
        json  |> Decode.storyWithComments
              |> stories => {
                   callback(stories);
                   resolve(())
                 }
       )
    |> ignore /* TODO: error handling */
  );
