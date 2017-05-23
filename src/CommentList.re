open Utils;

requireCSS "src/CommentList.css";

module IntSet =
  Set.Make {
    let compare = Pervasives.compare;
    type t = int;
  };

module CommentList = {
  include ReactRe.Component.Stateful;
  type props = {story: StoryData.story_with_comments};
  type state = {collapsed_comments: IntSet.t};
  let name = "CommentList";
  let getInitialState _ => {collapsed_comments: IntSet.empty};
  let toggleComment collapsed (idMaybe: option string) =>
    switch idMaybe {
    | Some idString =>
      let id = int_of_string idString;
      if (IntSet.mem id collapsed) {
        IntSet.remove id collapsed
      } else {
        IntSet.add id collapsed
      }
    | None => collapsed
    };
  let getCommentIdFromEvent (event: ReactEventRe.Mouse.t) =>
    getAttribute (ReactDOMRe.domElementToObj (ReactEventRe.Mouse.currentTarget event)) "name";
  let handleToggle {state} event =>
    Some {
      collapsed_comments: toggleComment state.collapsed_comments (getCommentIdFromEvent event)
    };
  let renderCommentText (textMaybe: option string) =>
    switch textMaybe {
    | Some text => <div dangerouslySetInnerHTML=(dangerousHtml text) />
    | None => textEl "missing comment"
    };
  let rec renderCommentKids componentBag story (comment: StoryData.comment_present) =>
    renderCommentList componentBag story comment.kids
  and renderComment componentBag (id: int) (story: StoryData.story_with_comments) => {
    let commentMaybe = JSMap.get story.comments id;
    let commentContent =
      switch commentMaybe {
      | Some commentPresentOrDeleted =>
        switch commentPresentOrDeleted {
        | StoryData.CommentPresent comment =>
          let openComment = not (IntSet.mem comment.id componentBag.state.collapsed_comments);
          let commentBody =
            if openComment {
              <div className="CommentList_commentBody">
                (renderCommentText comment.text)
                (renderCommentKids componentBag story comment)
              </div>
            } else {
              <noscript />
            };
          <div className="CommentList_comment">
            <div
              className="CommentList_disclosureRow CommentList_inline"
              name=(string_of_int comment.id)
              onClick=(componentBag.updater handleToggle)>
              <img
                alt=(openComment ? "hide" : "show")
                src=(
                      openComment ?
                        requireAssetURI "src/disclosure90.png" :
                        requireAssetURI "src/disclosure.png"
                    )
                className="CommentList_disclosure CommentList_muted"
              />
              <span className="CommentList_muted">
                (textEl (" " ^ fromNow comment.time ^ " by " ^ comment.by))
              </span>
            </div>
            commentBody
          </div>
        | StoryData.CommentDeleted _ => <div> (textEl "[deleted]") </div>
        }
      | None => raise Exit
      };
    <div key=(string_of_int id)> commentContent </div>
  }
  and renderCommentList componentBag story commentIds =>
    switch commentIds {
    | Some ids =>
      let commentList = Array.map (fun id => renderComment componentBag id story) ids;
      <div> (ReactRe.arrayToElement commentList) </div>
    | None => <div />
    };
  let render componentBag =>
    renderCommentList componentBag componentBag.props.story componentBag.props.story.kids;
};

include ReactRe.CreateComponent CommentList;

let createElement ::story => wrapProps {story: story};
