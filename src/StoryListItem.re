open Utils;

requireCSS "src/StoryListItem.css";

let commentIcon = requireAssetURI "src/comment.png";

module StoryListItem = {
  include ReactRe.Component;
  let name = "StoryListItem";
  type props = {story: StoryData.story, index: int};
  let renderTitle (story: StoryData.story, index: int) => {
    let content =
      <div className="StoryListItem_storyTitle">
        (intEl (index + 1))
        (textEl ". ")
        <span className="StoryListItem_storyTitleText"> (textEl story.title) </span>
      </div>;
    let link =
      switch story.url {
      | Some url => <a href=url className="StoryListItem_link"> content </a>
      | None =>
        <a href=("#/comments/" ^ string_of_int story.id) className="StoryListItem_link">
          content
        </a>
      };
    <div> link </div>
  };
  let renderByline (story: StoryData.story) =>
    <div className="StoryListItem_row StoryListItem_byline">
      /* TODO: badge */

        <span className="StoryListItem_number"> (intEl story.score) </span>
        (textEl " points")
        <span>
          <span className="StoryListItem_storyTime">
            (textEl (" submitted " ^ fromNow story.time ^ " by " ^ story.by))
          </span>
        </span>
      </div>;
  let renderArticleButton (story: StoryData.story, index: int) =>
    <div className="StoryListItem_flexRow">
      <div className="StoryListItem_storyCell">
        (renderTitle (story, index))
        (renderByline story)
      </div>
    </div>;
  let renderCommentsButton (story: StoryData.story) =>
    <div className="StoryListItem_commentsCell">
      <a href=("#/comments/" ^ string_of_int story.id) className="StoryListItem_link">
        <div> <img alt="comments" className="StoryListItem_icon" src=commentIcon /> </div>
        <div>
          <span className="StoryListItem_commentsText">
            <span className="StoryListItem_number"> (intEl story.descendants) </span>
            (textEl " comments")
          </span>
        </div>
      </a>
    </div>;
  let render {props} =>
    <div className="StoryListItem_itemRow">
      (renderArticleButton (props.story, props.index))
      (renderCommentsButton props.story)
    </div>;
};

include ReactRe.CreateComponent StoryListItem;

let createElement ::story ::index => wrapProps {story, index};
