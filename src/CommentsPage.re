open Utils;

requireCSS("src/CommentsPage.css");

type state = {story_with_comments: option(StoryData.story_with_comments)};

let name = "CommentsPage";

[@bs.deriving {accessors: accessors}]
type action =
  | Loaded(StoryData.story_with_comments);

let component = ReasonReact.reducerComponent(name);

let make = (~id, _children) => {
  let renderTitle = (story: StoryData.story_with_comments) => {
    let title = <h2 className="CommentsPage_title"> (textEl(story.title)) </h2>;
    let link =
      switch story.url {
      | Some(url) => <a href=url className="CommentsPage_titleLink"> title </a>
      | None => title
      };
    <div> link </div>
  };
  let renderByline = (story: StoryData.story_with_comments) =>
    <div>
      <span> (intEl(story.score)) </span>
      (textEl(" points"))
      <span>
        <span> (textEl(" submitted " ++ (fromNow(story.time) ++ (" by " ++ story.by)))) </span>
      </span>
    </div>;
  {
    ...component,
    initialState: () => {story_with_comments: None},
    reducer: (action, _state) =>
      switch action {
      | Loaded(data) => ReasonReact.Update({story_with_comments: Some(data)})
      },
    didMount: (self) => {
      StoryData.fetchStoryWithComments(id, self.reduce(loaded)) |> ignore;
      ReasonReact.NoUpdate
    },
    render: ({state}) => {
      let commentList =
        switch state.story_with_comments {
        | Some(story) =>
          <div> (renderTitle(story)) (renderByline(story)) <CommentList story /> </div>
        | None => ReasonReact.stringToElement("loading")
        };
      <div> commentList </div>
    }
  }
};
