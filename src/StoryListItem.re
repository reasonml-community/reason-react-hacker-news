open Utils;

requireCSS("src/StoryListItem.css");

let commentIcon = requireAssetURI("src/comment.png");

let component = ReasonReact.statelessComponent("StoryListItem");

let make = (~story: StoryData.story, ~index: int, _children) => {
  let renderIndex = () =>
    <aside className="StoryListItem_storyIndex">
      (ReasonReact.string(string_of_int(index + 1)))
    </aside>;
  let renderTitle = () => {
    let content = ReasonReact.string(story.title);
    <header className="StoryListItem_storyTitle">
      (
        switch (story.url) {
        | Some(url) =>
          <a href=url className="StoryListItem_link" target="_blank">
            content
          </a>
        | None =>
          <Link
            href=("/comments/" ++ string_of_int(story.id))
            className="StoryListItem_link">
            content
          </Link>
        }
      )
    </header>;
  };
  let renderByline = () =>
    <div className="StoryListItem_row StoryListItem_byline">
      /* TODO: badge */

        <span className="StoryListItem_number">
          <b> (ReasonReact.string(string_of_int(story.score))) </b>
          (ReasonReact.string(" points"))
        </span>
        <span className="StoryListItem_storyTime">
          {
            let time = story.time;
            let by = story.by;
            ReasonReact.string({j| submitted $time by $by|j});
          }
        </span>
      </div>;
  let renderArticleButton = () =>
    <div className="StoryListItem_flexRow">
      (renderIndex())
      <div className="StoryListItem_storyCell">
        (renderTitle())
        (renderByline())
      </div>
    </div>;
  let renderCommentsButton = () =>
    <div className="StoryListItem_commentsCell">
      <Link
        href=("/comments/" ++ string_of_int(story.id))
        className="StoryListItem_link">
        <div>
          <img alt="comments" className="StoryListItem_icon" src=commentIcon />
        </div>
        <div>
          <span className="StoryListItem_commentsText">
            <span className="StoryListItem_number">
              (ReasonReact.string(string_of_int(story.descendants)))
            </span>
            (ReasonReact.string(" comments"))
          </span>
        </div>
      </Link>
    </div>;
  {
    ...component,
    render: _self =>
      <div className="StoryListItem_itemRow">
        (renderArticleButton())
        (renderCommentsButton())
      </div>,
  };
};
