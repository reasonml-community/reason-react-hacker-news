open Utils;

requireCSS "src/CommentsPage.css";

module CommentsPage = {
  include ReactRe.Component.Stateful;
  type props = {id: int};
  type state = {story_with_comments: option StoryData.story_with_comments};
  let name = "CommentsPage";
  let handleLoaded _ data => Some {story_with_comments: Some data};
  let getInitialState _ => {story_with_comments: None};
  let componentDidMount {updater, props} => {
    StoryData.fetchStoryWithComments props.id (updater handleLoaded);
    None
  };
  let renderTitle (story: StoryData.story_with_comments) => {
    let title = <h2 className="CommentsPage_title"> (textEl story.title) </h2>;
    let link =
      switch story.url {
      | Some url => <a href=url className="CommentsPage_titleLink"> title </a>
      | None => title
      };
    <div> link </div>
  };
  let renderByline (story: StoryData.story_with_comments) =>
    <div>
      <span> (intEl story.score) </span>
      (textEl " points")
      <span>
        <span> (textEl (" submitted " ^ fromNow story.time ^ " by " ^ story.by)) </span>
      </span>
    </div>;
  let render {state} => {
    let commentList =
      switch state.story_with_comments {
      | Some story => <div> (renderTitle story) (renderByline story) <CommentList story /> </div>
      | None => ReactRe.stringToElement "loading"
      };
    <div> commentList </div>
  };
};

include ReactRe.CreateComponent CommentsPage;

let createElement ::id => wrapProps {id: id};
